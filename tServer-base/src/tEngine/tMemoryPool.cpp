#include "tMemoryPool.h"
#include "tLog.h"

tMemoryPool::tMemoryPool()
{
	TTHREAD_INITMUTEX(m_mutex);
}
tMemoryPool::~tMemoryPool()
{
	//遍历内存块存入到容器中
	TTHREAD_MUTEXLOCK(m_mutex);
	std::vector<SMEMORYBLOCK*> vBlock;
	while (m_psBlock)
	{
		//printf("Set指针m_psBlock:%p\n", m_psBlock);
		vBlock.push_back(m_psBlock);
		m_psBlock = m_psBlock->sHead.pNext;
	}
	
	//遍历内存块容器，释放每个内存块和内存块的数据区,lambda表达式
	for_each(vBlock.begin(), vBlock.end(), [](SMEMORYBLOCK* elem)
	{
		//printf("Get指针*iter:%p\n", elem);
		void *pMemoryData = reinterpret_cast<void*>(elem->sHead.pFirstUnit);
		SMEMORYDATA::operator delete(pMemoryData);
		delete(elem);
	});
	TTHREAD_MUTEXUNLOCK(m_mutex);
	TTHREAD_FINITMUTEX(m_mutex);
}

bool tMemoryPool::initMemoryPool(const TUSHORT nUnitSize, TUSHORT nUnitCount, TUSHORT nMinBlockCount)
{
	if(nUnitSize<8){return false;}
	m_nUnitSize = nUnitSize;
	m_nUnitCount = nUnitCount;
	m_nMinBlockCount = nMinBlockCount;
	m_nCurrentBlockCount = nMinBlockCount;

	TLOGI("==========Init memorypool ==================");
	m_psBlock = nullptr;
	for (int i = 0; i < nMinBlockCount; i++)
	{
		SMEMORYBLOCK* p = new SMEMORYBLOCK;
		p->sHead.pNext = m_psBlock;
		m_psBlock = p;
		m_psBlock->sHead.nFreeSize = m_nUnitSize*m_nUnitCount;
		m_psBlock->sHead.nMemoryCount = m_nUnitCount;
		m_psBlock->sHead.nMemorySize = m_nUnitSize*m_nUnitCount;
		m_psBlock->sHead.nMinBlockCount = m_nMinBlockCount;
		m_psBlock->sData.pFreeUnit = reinterpret_cast<SUNITMEMORYOBJ*>(SMEMORYDATA::operator new(m_psBlock->sHead.nMemorySize));
		m_psBlock->sHead.pFirstUnit = m_psBlock->sData.pFreeUnit;
		m_psBlock->sHead.nUnitSize = m_nUnitSize;
		SUNITMEMORYOBJ* pTemp = m_psBlock->sData.pFreeUnit;
		for (int j = 0; j < m_psBlock->sHead.nMemoryCount-1; ++j)
		{
			pTemp->pNext = (SUNITMEMORYOBJ*)((char*)pTemp + m_psBlock->sHead.nUnitSize);
			pTemp = pTemp->pNext;
		}
		pTemp->pNext = nullptr;  // 最后一个
	}
	TLOGI("== UnitSize:%d个", m_nUnitSize);
	TLOGI("== UnitCount:%d", m_nUnitCount);
	TLOGI("== MinBlockCount:%d个", m_nMinBlockCount);
	TLOGI("==========Init memorypool success!==========");
	return true;
}

void* tMemoryPool::fnMalloc()
{
	SMEMORYBLOCK* psCurrentBlock = m_psBlock;
	void* pReturn;
	while (true)
	{
		if(!psCurrentBlock)
		{
			psCurrentBlock = new SMEMORYBLOCK;
			psCurrentBlock->sHead.nFreeSize = m_nUnitSize*m_nUnitCount;
			psCurrentBlock->sHead.nMemoryCount = m_nUnitCount;
			psCurrentBlock->sHead.nMemorySize = m_nUnitSize*m_nUnitCount;
			psCurrentBlock->sHead.nMinBlockCount = m_nMinBlockCount;
			psCurrentBlock->sHead.nUnitSize = m_nUnitSize;
			psCurrentBlock->sData.pFreeUnit = reinterpret_cast<SUNITMEMORYOBJ*>(SMEMORYDATA::operator new(psCurrentBlock->sHead.nMemorySize));
			psCurrentBlock->sHead.pFirstUnit = psCurrentBlock->sData.pFreeUnit;
			SUNITMEMORYOBJ* pTemp = psCurrentBlock->sData.pFreeUnit;
			for (int i = 0; i < psCurrentBlock->sHead.nMemoryCount-1; ++i)
			{
				pTemp->pNext = (SUNITMEMORYOBJ*)((char*)pTemp + psCurrentBlock->sHead.nUnitSize);
				pTemp = pTemp->pNext;
			}
			pTemp->pNext = nullptr;
			TTHREAD_MUTEXLOCK(m_mutex);
			psCurrentBlock->sHead.pNext = m_psBlock;
			m_psBlock = psCurrentBlock;
			m_nCurrentBlockCount++;
			TTHREAD_MUTEXUNLOCK(m_mutex);
			continue;
		}
		//当前内存块可分配内存大小小于需要开辟的内存大小，则查看下一块内存
		else if (psCurrentBlock->sHead.nFreeSize < psCurrentBlock->sHead.nUnitSize)
		{
			TTHREAD_MUTEXLOCK(m_mutex);
			psCurrentBlock = psCurrentBlock->sHead.pNext;
			TTHREAD_MUTEXUNLOCK(m_mutex);
			continue;
		}
		else
		{
			TTHREAD_MUTEXLOCK(m_mutex);
			pReturn = reinterpret_cast<void*>(psCurrentBlock->sData.pFreeUnit);
			psCurrentBlock->sHead.nFreeSize -= psCurrentBlock->sHead.nUnitSize;
			psCurrentBlock->sData.pFreeUnit = psCurrentBlock->sData.pFreeUnit->pNext;
			TTHREAD_MUTEXUNLOCK(m_mutex);
			break;
		}
	}
	return pReturn;
}

bool tMemoryPool::fnFree(void* p)
{
	bool bRet = true;
	SMEMORYBLOCK* psCurrentBlock = m_psBlock;
	SMEMORYBLOCK* psLastBlock = nullptr;
	while (true)
	{
		if (!psCurrentBlock)
		{
			printf("his memory not in these memorypool,p=%p!!\n", p);
			bRet = false;
			break;
		}
		
		else if ((psCurrentBlock->sHead.pFirstUnit <= p) && (p <= ((char*)(psCurrentBlock->sHead.pFirstUnit) + psCurrentBlock->sHead.nMemorySize - m_psBlock->sHead.nUnitSize)))
		{
			TTHREAD_MUTEXLOCK(m_mutex);
			((SUNITMEMORYOBJ*)p)->pNext = psCurrentBlock->sData.pFreeUnit;
			psCurrentBlock->sData.pFreeUnit = (SUNITMEMORYOBJ*)p;
			psCurrentBlock->sHead.nFreeSize += psCurrentBlock->sHead.nUnitSize;
			if ((psCurrentBlock->sHead.nFreeSize == psCurrentBlock->sHead.nMemorySize) && (m_nCurrentBlockCount > m_nMinBlockCount))
			{
				//当删除的内存块不在内存块链的首部（内存链中内存块数量>2），则将上一块内存的next指针指向当前内存块的下一个内存块
				if (psLastBlock)
				{
					psLastBlock->sHead.pNext = psCurrentBlock->sHead.pNext;
				}
				//当删除的内存块为内存块链的首块,且内存池中内存块个数大于1，将m_psBlock指向下一块内存
				else if (!psLastBlock && m_nCurrentBlockCount > 1)
				{
					m_psBlock = psCurrentBlock->sHead.pNext;
				}
				//当删除的内存块为内存块链的首块,且内存池中内存块个数等于1，只有最小内存块数设置为0时，才删除该内存块，令m_psBlock指向空
				else if (!psLastBlock && m_nCurrentBlockCount == 1 && m_nMinBlockCount < 1)
				{
					m_psBlock = nullptr;
				}
				SMEMORYDATA::operator delete(psCurrentBlock->sHead.pFirstUnit);
				delete(psCurrentBlock);
				m_nCurrentBlockCount--;
			}
			TTHREAD_MUTEXUNLOCK(m_mutex);
			break;
		}
		else
		{
			//向后访问，无需加锁，fnMalloc只会向前插内存块
			psLastBlock	= psCurrentBlock;
			psCurrentBlock = psCurrentBlock->sHead.pNext;
		}
	}
	return bRet;
}

int tMemoryPool::getCapacity()
{
	return m_nCurrentBlockCount;
}