#ifndef DataStruct_H
#define DataStruct_H
#include "stdio.h"
#include "time.h"
#include "string.h"

typedef struct Card{
	char aName[18];         // ����
	char aPwd[8];           // ����
	int  nStatus;           // ��״̬(0-δ�ϻ���1-�����ϻ���2-��ע����3-ʧЧ)
	time_t tStart;          // ����ʱ��
	time_t tEnd;            // ���Ľ�ֹʱ�� 
	float fTotalUse;        // �ۼƽ��
	time_t tLast;           // ���ʹ��ʱ��
	int nUseCount;          // ʹ�ô���
	float fBalance;         // ���
	int nDel;               // ɾ����ʶ 0-δɾ��,1-ɾ��
}Card;

typedef struct CardNode{
	Card cardData;
	struct CardNode *next;
}CardNode, *lpCardNode;

typedef struct Billing {
	char aCardName[18];
	time_t tStart;
	time_t tEnd;
	int nStatus;
	float fAmount;
	int nDel;
}Billing;

typedef struct BillingNode{
	Billing BillingData;
	struct BillingNode *next;
}BillingNode, *lpBillingNode;

typedef struct LogonInfo{
	char aCardName[18];
	float fBalance;
	time_t tLogon;
}LogonInfo;

typedef struct LogoutInfo{
	char aCardName[18];
	float fAmount;
	float fBalance;
	time_t tStart;
	time_t tEnd;
}LogoutInfo;
#endif