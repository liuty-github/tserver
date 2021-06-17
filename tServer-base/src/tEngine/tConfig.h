
#ifndef __TCONFIG_H__
#define __TCONFIG_H__

#include "tDefine.h"
typedef struct SCONFITEM
	{
		char ItemName[50];
		char ItemContent[500];
	}*LPSCONFITEM;
//类名可以遵照一定的命名规则规范，比如老师这里，第一个字母是C，后续的单词首字母大写
class tConfig
{
private:
	tConfig();
public:
	~tConfig();
	TEXPORTS static tConfig* getInstance();
    TEXPORTS bool 		 	 initConfig(const char *pconfName); //装载配置文件
	TEXPORTS const char* 	 getString(const char *p_itemname);
	TEXPORTS int  		 	 getIntDefault(const char *p_itemname,const int def);

private:
	void Rtrim(char *string);
	void Ltrim(char *string);
private:
	std::vector<LPSCONFITEM> m_ConfigItemList; //存储配置信息的列表

};

#endif
