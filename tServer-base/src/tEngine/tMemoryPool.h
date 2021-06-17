#include "tDefine.h"

#ifndef __MEMORYPOOL_H__
#define __MEMORYPOOL_H__
/************************************说明******************************************/


/***********************************SUNITMEMORYOBJ*********************************
嵌入式指针结构体
**********************************************************************************/
struct SUNITMEMORYOBJ
{
	struct SUNITMEMORYOBJ* pNext;
};

/**********************************SMEMORYHEAD*************************************
说明					内存块链头部
Ushort					nMemoryCount记录数据区内存的内存单元个数									
Ushort					nUnitSize记录数据区每一内存单元的大小（byte）								
TUINT32					nMemorySize不含结构体头部开辟的内存大小
Ushort					nFreeSize未分配出去的内存大小
Ushort					nMinBlockCount最小内存块数，即一个内存块的全部为可分配状态，
						也不进行释放	
SUNITMEMORYOBJ*			pFirstUnit指向该内存块链的首个内存单元
SMEMORYBLOCK*			pNext指向下一个MemoryBlock
**********************************************************************************/
struct SMEMORYBLOCK;
struct SMEMORYHEAD
{
	friend struct	 SMEMORYBLOCK;
	TUSHORT          nMemoryCount;
	TUSHORT			 nUnitSize;
	TUINT32			 nMemorySize;
	TUSHORT          nFreeSize;
	TUSHORT          nMinBlockCount;
	SUNITMEMORYOBJ*  pFirstUnit = 0x00;
	SMEMORYBLOCK*	 pNext = 0x00;
};

/***********************************SMEMORYDATA***********************************
说明					内存块链数据区
operator new			重载new，使用malloc效率比new更高
operator delete			重载delete使用free
SUNITMEMORYOBJ*			pFreeUnit嵌入式指针，指向下一个可分配的内存单元
**********************************************************************************/
struct SMEMORYDATA
{
	void* operator new(size_t size)
	{
		return malloc(size);
	}
	void  operator delete(void *p)
	{
		free(p);
	}
	SUNITMEMORYOBJ*  pFreeUnit;
};
/***********************************SMEMORYBLOCK***********************************
说明					内存块链
SMEMORYHEAD				sHead内存块链头部
SMEMORYDATA				sData内存块链数据区
**********************************************************************************/
struct SMEMORYBLOCK
{
	SMEMORYHEAD		 sHead;
	SMEMORYDATA	     sData;
};
/***********************************tMemoryPool************************************
说明					内存池类
tMemoryPool				构造函数
入参：
uUnitSize				每个内存单元的字节数，因为使用了嵌入式指针，该入参的值必须大
						于等于8
nUnitCount				每个内存块链的内存单元个数，该入参的值必须大于等于1
nMinBlockCount			最下内存块链数，即内存池在无内存使用时保持的内存链数，该入参
						需大于等于0

fnMalloc()				申请内存
入参：					无，默认申请的字节数等于m_nUnitCount
返回值：				返回void*指针，该指针指向申请内存区域的首地址

fnFree(void* p)			释放内存
入参：					释放内存区域的首地址，若传入的指针地址不属于内存池，则不进行
						释放
返回值：				释放成功时返回ture，失败时返回false
**********************************************************************************/
 class tMemoryPool
{
public:

	tMemoryPool();
	~tMemoryPool();
	TEXPORTS bool			initMemoryPool(TUSHORT nUnitSize = 8, TUSHORT nUnitCount = 256, TUSHORT nMinBlockCount = 3);
	TEXPORTS void*          fnMalloc();
	TEXPORTS bool           fnFree(void* p);
	TEXPORTS int			getCapacity();
private:
	SMEMORYBLOCK*	 		m_psBlock;	//指向内存块链中的首个内存块
	TUSHORT			 		m_nUnitSize;		//内存块中每个内存单元的大小
	TUSHORT			 		m_nUnitCount;	//初始化时每个内存块的内存单元数量
	TUSHORT			 		m_nMinBlockCount;	//最小内存块数，即内存池就算没人使用时，也保留MinBlockCount块的内存块
	TUSHORT			 		m_nCurrentBlockCount;//内存池中当前的内存块数
	TTHREAD_MUTEX 			m_mutex;
};

#endif