#ifndef BILLING_SERVICE_H
#define BILLING_DERVICE_H
#include "DataStruct.h"
int initBillingList();
int getBilling();
void releaseBillingList();
Billing *checkBilling(const char *pName,int *pIndex);
#endif