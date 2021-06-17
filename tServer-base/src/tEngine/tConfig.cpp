#include "tConfig.h"

//静态成员赋值
static tConfig* g_instance = nullptr;

//构造函数
tConfig::tConfig()
{		
}

//析构函数
tConfig::~tConfig()
{    
	std::vector<LPSCONFITEM>::iterator pos;	
	for(pos = m_ConfigItemList.begin(); pos != m_ConfigItemList.end(); ++pos)
	{		
		delete (*pos);
	}//end for
	m_ConfigItemList.clear(); 
    return;
}

tConfig* tConfig::getInstance()
{	
    if(g_instance == nullptr)
    {
        //锁
        if(g_instance == nullptr)
        {					
            g_instance = new tConfig();
        }
        //放锁		
    }
    return g_instance;
}
//装载配置文件
bool tConfig::initConfig(const char *pconfName) 
{   
    FILE *fp;
    fp = fopen(pconfName,"r");
    if(fp == NULL)
        return false;

    
    char  linebuf[501];   

    while(!feof(fp))  
    {    
        if(fgets(linebuf,500,fp) == NULL) 
            continue;

        if(linebuf[0] == 0)
            continue;

        if(*linebuf==';' || *linebuf==' ' || *linebuf=='#' || *linebuf=='\t'|| *linebuf=='\n')
			continue;
        
    lblprocstring:
		if(strlen(linebuf) > 0)
		{
			if(linebuf[strlen(linebuf)-1] == 10 || linebuf[strlen(linebuf)-1] == 13 || linebuf[strlen(linebuf)-1] == 32) 
			{
				linebuf[strlen(linebuf)-1] = 0;
				goto lblprocstring;
			}		
		}
        if(linebuf[0] == 0)
            continue;
        if(*linebuf=='[')
			continue;

        char *ptmp = strchr(linebuf,'=');
        if(ptmp != NULL)
        {
            LPSCONFITEM p_confitem = new SCONFITEM;                    //注意前边类型带LP，后边new这里的类型不带
            memset(p_confitem,0,sizeof(SCONFITEM));
            strncpy(p_confitem->ItemName,linebuf,(int)(ptmp-linebuf)); //等号左侧的拷贝到p_confitem->ItemName
            strcpy(p_confitem->ItemContent,ptmp+1);                    //等号右侧的拷贝到p_confitem->ItemContent

            Rtrim(p_confitem->ItemName);
			Ltrim(p_confitem->ItemName);
			Rtrim(p_confitem->ItemContent);
			Ltrim(p_confitem->ItemContent);
          
            m_ConfigItemList.push_back(p_confitem);  //内存要释放，因为这里是new出来的 
        } 
    } 

    fclose(fp);
    return true;
}

//根据ItemName获取配置信息字符串，不修改不用互斥
const char *tConfig::getString(const char *p_itemname)
{
	std::vector<LPSCONFITEM>::iterator pos;	
	for(pos = m_ConfigItemList.begin(); pos != m_ConfigItemList.end(); ++pos)
	{	
		if(strcasecmp( (*pos)->ItemName,p_itemname) == 0)
			return (*pos)->ItemContent;
	}
	return NULL;
}
//根据ItemName获取数字类型配置信息，不修改不用互斥
int tConfig::getIntDefault(const char *p_itemname,const int def)
{
	std::vector<LPSCONFITEM>::iterator pos;	
	for(pos = m_ConfigItemList.begin(); pos !=m_ConfigItemList.end(); ++pos)
	{	
		if(strcasecmp( (*pos)->ItemName,p_itemname) == 0)
			return atoi((*pos)->ItemContent);
	}
	return def;
}


//截取字符串尾部空格
void tConfig::Rtrim(char *string)   
{   
	size_t len = 0;   
	if(string == NULL)   
		return;   

	len = strlen(string);   
	while(len > 0 && string[len-1] == ' ')   //位置换一下   
		string[--len] = 0;   
	return;   
}

//截取字符串首部空格
void tConfig::Ltrim(char *string)
{
	size_t len = 0;
	len = strlen(string);   
	char *p_tmp = string;
	if( (*p_tmp) != ' ') //不是以空格开头
		return;
	//找第一个不为空格的
	while((*p_tmp) != '\0')
	{
		if( (*p_tmp) == ' ')
			p_tmp++;
		else
			break;
	}
	if((*p_tmp) == '\0') //全是空格
	{
		*string = '\0';
		return;
	}
	char *p_tmp2 = string; 
	while((*p_tmp) != '\0')
	{
		(*p_tmp2) = (*p_tmp);
		p_tmp++;
		p_tmp2++;
	}
	(*p_tmp2) = '\0';
    return;
}