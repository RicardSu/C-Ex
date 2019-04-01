#ifndef CARD_FILE_H
#define CARD_FILE_H
#include"DataStruct.h"
int saveCard(const Card *pCard,const char* pPath);
int readCard(Card* pCard,const char* pPath);
int getCardCount(const char* pPath);
int updateCard(const Card* pCard,const char* pPath,int nIndex);
Card praseCard(char* pBuf);
#endif