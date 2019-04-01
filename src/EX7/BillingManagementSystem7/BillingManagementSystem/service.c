#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "DataStruct.h"
#include "card_service.h"
#include "global.h"
#include "card_file.h"
#include "billing_file.h"
#include "billing_service.h"

lpCardNode cardList;
lpCardNode head;
lpCardNode p, q;

/*上机*/
int doLogon(const char *pName,const char* pPwd,LogonInfo *pInfo){
	Card *pCard =NULL;
	int nIndex=0;
	Billing billing;
	pCard=checkCard(pName,pPwd,&nIndex);
	if(pCard==NULL){
		return FALSE;
	}
	if(pCard->nStatus!=0){
		return UNUSE;
	}
	if(pCard->fBalance<=0){
		return INSUFFICIENTBALANCE;
	}
	pCard->nStatus=1;
	pCard->nUseCount++;
	pCard->tLast=time(NULL);
	if(updateCard(pCard,CARDPATH,nIndex)==FALSE){
		return FALSE;
	}
	strcpy(billing.aCardName,pName);
	billing.tStart=time(NULL);
	billing.tEnd=0;
	billing.nStatus=0;
	billing.fAmount=0;
	billing.nDel=0;
	if(saveBilling(&billing,BILLINGPATH)==TRUE){
		strcpy(pInfo->aCardName,pName);
		pInfo->fBalance=pCard->fBalance;
		pInfo->tLogon=billing.tStart;
	}
	return TRUE;

}
/*下机*/
int doLogout(const char *pName,const char* pPwd,LogoutInfo *pInfo){
	Card *pCard =NULL;
	Billing *pBilling=NULL;
	int nIndex=0;
	int nIndex1=0;
	float cost=0;
	int costTime=0;
	float costMoney=0;
	pCard=checkCard(pName,pPwd,&nIndex);
	if(pCard==NULL)
	return FALSE;
	if(pCard->nStatus!=1){
		return UNUSE;
	}
	/*更新卡信息和账单信息*/
	pCard->nStatus=0;
	pBilling=checkBilling(pName,&nIndex1);
	pBilling->nStatus=1;
	pBilling->tEnd=time(NULL);
	cost=(float)difftime(pBilling->tStart,pBilling->tStart);
	costTime=(int)(cost/60)+1;
	if(costTime%UNIT==0){
		costMoney=(int)(costTime/UNIT)*CHARGE;
	}
	else{
		costMoney=(int)(costTime/UNIT+1)*CHARGE;
	}
		pBilling->fAmount=costMoney;
		pCard->fBalance-=costMoney;
		pCard->fTotalUse+=costMoney;		
	if(updateBilling(pBilling,BILLINGPATH,nIndex1)==TRUE&&(updateCard(pCard,CARDPATH,nIndex)==TRUE)){
		strcpy(pInfo->aCardName,pName);
		pInfo->fAmount=pBilling->fAmount;
		pInfo->fBalance=pCard->fBalance;
		pInfo->tStart=pBilling->tStart;
		pInfo->tEnd=pBilling->tEnd;
	}
	return TRUE;
}

/*卡充值函数*/
int saveMoney(const char* pName, const char* pPwd) {
	lpCardNode cardNode = NULL;
	float charge = 0;
	int nIndex = 0;
	if (FALSE == getCard()) {
		return FALSE;
	}
	cardNode = cardList->next;
	//遍历链表，判断能否进行充值
	while (cardNode != NULL){
		if (strcmp(cardNode->cardData.aName, pName) == 0 && strcmp(cardNode->cardData.aPwd, pPwd) == 0 && (cardNode->cardData.nStatus != 2)){
			printf("请输入充值的金额：");
			scanf("%f", &charge);
			cardNode->cardData.fBalance += charge;
			if (updateCard(&cardNode->cardData, CARDPATH, nIndex) == TRUE){
				return TRUE;
			}
		}
		cardNode = cardNode->next;
		nIndex++;
	}
	return FALSE;
}

/*卡退费函数*/
int returnMoney(const char* pName, const char* pPwd) {
	lpCardNode cardNode = NULL;
	float charge = 0;
	int nIndex = 0;
	/*得到文件中的卡信息*/
	if (FALSE == getCard()){
		return FALSE;
	}
	cardNode = cardList->next;
	while (cardNode != NULL){
		if (strcmp(cardNode->cardData.aName, pName) == 0 && strcmp(cardNode->cardData.aPwd, pPwd) == 0){
			printf("退费金额：%f\n", cardNode->cardData.fBalance);
			cardNode->cardData.fBalance = 0.0;
			/*如果可以退费，更新文件卡信息*/
			if (updateCard(&cardNode->cardData, CARDPATH, nIndex) == TRUE){
				return TRUE;
			}
		}
		cardNode = cardNode->next;
		nIndex++;
	}
	return FALSE;
}

/*注销卡函数*/
int canCel(const char* pName, const char* pPwd) {
	lpCardNode cardNode = NULL;
	float charge = 0;
	int nIndex = 0;
	/*得到文件中卡信息*/
	if (FALSE == getCard()){
		return FALSE;
	}
	cardNode = cardList->next;
	/*遍历链表，判断能否进行注销*/
	while (cardNode != NULL){
		if (strcmp(cardNode->cardData.aName, pName) == 0 && strcmp(cardNode->cardData.aPwd, pPwd) == 0){
			/*0状态表示可以注销*/
			if (cardNode->cardData.nStatus != 0){
				return FALSE;
			}
			if (cardNode->cardData.fBalance < 0){
				return FALSE;
			}
			/*更新信息*/
			printf("卡号：\t退费金额\n");
			printf("%s\t%.1f\n\n", cardNode->cardData.aName, cardNode->cardData.fBalance);
			cardNode->cardData.nStatus = 2;
			printf("所输入卡号状态更变为：%d\n", cardNode->cardData.nStatus);
			cardNode->cardData.fBalance = 0.0;
			/*如果可以注销，更新文件卡信息*/
			if (updateCard(&cardNode->cardData, CARDPATH, nIndex) == TRUE){
				return TRUE;
			}
		}
		cardNode = cardNode->next;
		nIndex++;
	}
	return FALSE;
}



