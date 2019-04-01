#ifndef SERVICE_H
#define SERVICE_H
#include "DataStruct.h"
int doLogon(const char* pName,const char* pPwd,LogonInfo *pInfo);
int doLogout(const char *pName,const char* pPwd,LogoutInfo *pInfo);
int saveMoney(const char* pName, const char* pPwd);
int returnMoney(const char* pName, const char* pPwd);
int canCel(const char* pName, const char* pPwd);
#endif