#ifndef CARD_SERVICE_H
#define CARD_SERVICE_H
int initCardList();
int addCard(Card ncard);
void releaseCardList();
Card *queryCard(const char name[]);
Card *queryCards(const char name[], int *pIndex);
Card *checkCard(const char *pName, const char* pPwd, int *nIndex);
#endif