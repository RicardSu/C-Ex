#include "stdio.h"
#include "time.h"
#include "string.h"
#include "stdlib.h"
#include "DataStruct.h"
#include "service.h"
#include "card_service.h"
#include "tool.h"
#include "global.h"

int checklength(char aa[]);
void outputMenu(){
	printf("\n\n----------�˵�----------\n");
	printf("1.��ӿ�\n");
	printf("2.��ѯ��\n");
	printf("3.�ϻ�\n");
	printf("4.�»�\n");
	printf("5.��ֵ\n");
	printf("6.�˷�\n");
	printf("7.��ѯͳ��\n");
	printf("8.ע����\n");
	printf("0.�˳�\n");
	printf("������˵���ţ�");
}

/*��ӿ�*/
void add(){
	char name[18] = { '0' };
	char pname[1000];
	char password[8] = { '0' };
	char ppassword[1000];
	float money = 0.0;
	int nlength = 0;
	int plength = 0;
	Card card;
	struct tm* endTime;     // ��ֹʱ��
	struct tm* startTime;   // ����ʱ��
	int success;
	printf("\n\n----------��ӿ�----------\n");
	printf("�����뿨��<1-18λ>:");
	scanf("%s", &pname);

	if (checklength(pname) > 18) {
		printf("���ų���18λ������������\n");
		return;
	}
	else if (checklength(pname) < 1) {
		printf("���Ų���Ϊ�գ�����������\n");
		return;
	}
	else{
		strcpy(name, pname);
	}
	printf("����������<1-8λ>��");
	scanf("%s", &ppassword);
	if (checklength(ppassword) > 8) {
		printf("���볬��8λ������������\n");
		return;
	}
	else if (checklength(ppassword) < 1) {
		printf("���벻��Ϊ�գ�����������\n");
		return;
	}
	else{
		strcpy(password, ppassword);
	}
	printf("�����뿪�����<RMB>��");
	scanf("%f", &money);
	strcpy(card.aName, name);
	strcpy(card.aPwd, password);
	card.fTotalUse = 0;
	card.fBalance = money;
	card.nStatus = 0;
	card.nDel = 0;
	card.nUseCount = 0;
	card.tStart = card.tEnd = card.tLast = time(NULL);
	// ����ʱ�䣬��ֹʱ�䣬���ʹ��ʱ�䶼Ĭ��Ϊ��ǰʱ�䡣
	// ���ݿ���ʱ�䣬�����ֹʱ�䣬ÿ�ſ�����Ч��Ϊһ��
	startTime = localtime(&card.tStart);
	endTime = localtime(&card.tEnd);
	endTime->tm_year = startTime->tm_year + 1;
	card.tEnd = mktime(endTime);
	success = addCard(card);
	if (success == FALSE) {
		printf("\n\n���ʧ��!\n\n");
	}
	else {
		printf("\n��ӳɹ�!");
		printf("\n\n��ӿ�����Ϣ����\n");
		printf("����\t\t����\t\t״̬\t\t�������\n");
		printf("%s\t\t%s\t\t%d\t\t%.2f\n", card.aName, card.aPwd, card.nStatus, money);
	}
}

/*��ѯ��*/
void query() {
	char name[18];
	char pname[1000];
	/*char password[8];
	char ppassword[1000];*/
	char nTime[20];
	Card *qCard;
	int pIndex = 0;
	int i;
	//lpCardNode pCard;
	printf("\n\n----------��ѯ��---------\n");
	printf("�������ѯ�Ŀ���<����Ϊ1-18>:");
	scanf("%s", &pname);
	if (checklength(pname) > 18){
		printf("���ų���18λ������������\n");
		return;
	}
	else {
		strcpy(name, pname);
	}
	/*��ѯ����*/
	/*printf("�������ѯ�Ŀ���<����Ϊ1-8>:");
	scanf("%s",&ppassword);
	if(checklength(ppassword)>8){
		printf("���볬��8λ������������\n");
		return;
	}
	else{
		strcpy(password,ppassword);
	}
	*/
	/*��ȷ��ѯ
	qCard=queryCard(name);
	if(qCard==NULL){
		printf("δ��ѯ���˿���Ϣ\n");
	}
	else{
		printf("\n\n��ѯ���Ŀ���Ϣ���£�\n");
		timeToString(qCard->tLast,nTime);
		printf("����\t\t״̬\t\t���\t\t�ۼ�ʹ��\t\tʹ�ô���\t\t�ϴ�ʹ��ʱ��\n");
		printf("%s\t\t%d\t\t%.2f\t\t%.2f\t\t\t%d\t\t\t%s\n",qCard->aName,qCard->nStatus,qCard->fTotalUse,qCard->fBalance,qCard->nUseCount,nTime);
	}*/
	/*ģ����ѯ*/

	qCard = queryCards(name, &pIndex);
	if (qCard == NULL){
		printf("δ�鵽��ؿ���Ϣ\n");
	}
	else{
		printf("\n\n��ѯ���Ŀ���Ϣ���£�\n");
		printf("����\t\t״̬\t\t���\t\t�ۼ�ʹ��\t\tʹ�ô���\t\t�ϴ�ʹ��ʱ��\n");
		for (i = 0; i < pIndex; i++){
			timeToString(qCard[i].tLast, nTime);
			printf("%s\t\t%d\t\t%.2f\t\t%.2f\t\t\t%d\t\t\t%s\n", qCard[i].aName, qCard[i].nStatus, qCard[i].fBalance, qCard[i].fTotalUse, qCard[i].nUseCount, nTime);
		}
}

	/*���ݿ��ź������ѯ����Ϣ�����������������е�λ��*/

	/*pCard=checkCard(name,password);
	if(pCard==NULL)
	{
		printf("�ʺŻ������������������");
	}
	else
	{
		qCard=&(pCard->cardData);
		timeToString(qCard->tLast,nTime);
printf("����\t\t״̬\t\t���\t\t�ۼ�ʹ��\t\tʹ�ô���\t\t�ϴ�ʹ��ʱ��\n");
		printf("%s\t\t%d\t\t%.2f\t\t%.2f\t\t\t%d\t\t\t%s\n",qCard->aName,qCard->nStatus,qCard->fTotalUse,qCard->fBalance,qCard->nUseCount,nTime);
		printf("����Ϣ�ĵ�ַ��");
		printf("%d\n",pCard);
	}

	*/
}

/*�ϻ�����*/
void logon(){
	char aName[18] = { 0 };
	char aPwd[8] = { 0 };
	int nResult = 0;
	LogonInfo* pInfo = NULL;
	char aTime[TIMELENGTH] = { 0 };
	printf("----------�ϻ�----------\n");
	printf("\n�������ϻ����ţ�����Ϊ1-18����");
	scanf("%s", &aName);
	printf("\n�������ϻ����루����Ϊ1-8����");
	scanf("%s", &aPwd);
	pInfo = (LogonInfo*)malloc(sizeof(LogonInfo));
	nResult = doLogon(aName, aPwd, pInfo);
	switch (nResult){
		case 0:
			printf("�ϻ�ʧ��\n");
			break;
		case 1:
			printf("����\t���\t�ϻ�ʱ��\n");
			timeToString(pInfo->tLogon, aTime);
			printf("%s\t%.2f\t%s\n", pInfo->aCardName, pInfo->fBalance, aTime);
			break;
		case 2:
			printf("�ÿ������ϻ������Ѿ�ע��\n");
			break;
		case 3:
			printf("������\n");
			break;
		default:{
			break;
		}
	}
}

/*�»�*/
void logout(){
	char aName[18] = { 0 };
	char aPwd[8] = { 0 };
	int nResult = 0;
	char aTime1[TIMELENGTH] = { 0 };
	char aTime2[TIMELENGTH] = { 0 };
	LogoutInfo *pInfo = NULL;
	printf("----------�»�----------\n");
	printf("\n�������»����ţ�����Ϊ1-18����");
	scanf("%s", &aName);
	printf("\n�������»����루����Ϊ1-8����");
	scanf("%s", &aPwd);
	pInfo = (LogoutInfo*)malloc(sizeof(LogoutInfo));
	nResult = doLogout(aName, aPwd, pInfo);
	switch (nResult){
		case 0:
			printf("δ�鵽�ÿ��ϻ���Ϣ���»�ʧ��\n");
			break;
		case 1:
			timeToString(pInfo->tStart, aTime1);
			timeToString(pInfo->tEnd, aTime2);
			printf("----------�»���Ϣ����----------\n");
			printf("����\t����\t���\t�ϻ�ʱ��\t\t�»�ʱ��\n");
			printf("%s\t%.2f\t%.2f\t%s\t%s\n", pInfo->aCardName, pInfo->fAmount, pInfo->fBalance, aTime1, aTime2);
			break;
		case 2:
			printf("δ�鵽�ÿ��ϻ���Ϣ���»�ʧ��\n");
			break;
		default:{
			break;
		}
	}
}

/*��ֵ*/
void addMoney(){
	char aName[18] = { 0 };
	char aPwd[8] = { 0 };
	printf("\n�������ֵ�˺ţ�");
	scanf("%s",aName);
	printf("\n�������˺����룺");
	scanf("%s", aPwd);
	if (TRUE == saveMoney(aName, aPwd)) {
		printf("\n��ֵ�ɹ���\n");
	}
	else {
		printf("\n��ֵʧ�ܣ�\n");
	}
}

/*�˷�*/
void refundMoney(){
	char aName[18] = { 0 };
	char aPwd[8] = { 0 };
	printf("\n�������˺ţ�");
	scanf("%s", aName);
	printf("\n���������룺");
	scanf("%s", aPwd);
	if (TRUE == returnMoney(aName, aPwd)){
		printf("\n�˷ѳɹ�! \n");
	}
	else{
		printf("\n�˷�ʧ��! \n");
	}
}

/*ע����*/
void annul(){
	char aName[32] = { 0 };
	char aPwd[20] = { 0 };
	printf("\n�������˺ţ�");
	scanf("%s", aName);
	printf("\n���������룺");
	scanf("%s", aPwd);
	if (TRUE == canCel(aName, aPwd)){
		printf("\nע���ɹ�! \n");
	}
	else{
		printf("\nע��ʧ��! \n");
	}
}


/*���ݲ�ѯ*/
void queryStatistics() {
}

/*�˳�*/
void exitApp(){
	releaseCardList();/*�ͷ�����ռ�*/
	exit(0);
}

/*���ȼ��*/
int checklength(char aa[]){
	int count = 0;
	while (aa[count] != '\0') {
		count++;
	}
	return count;
}
