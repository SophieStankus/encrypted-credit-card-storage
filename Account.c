#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Account.h"

void CreateAccount(Account* thisAccount, char userInit[], char passwordInit[],
 char CCInit[], Account* nextAcct){
    strcpy(thisAccount -> userName, userInit);
    strcpy(thisAccount -> password, passwordInit);
    strcpy(thisAccount -> eCC, CCInit);
    thisAccount -> nextAcc = nextAcct;
}

void InsertAccountAfter(Account* thisAccount, Account* newAccount){
    Account* temp = NULL;
   temp = thisAccount->nextAcc;
   thisAccount->nextAcc = newAccount;
   newAccount->nextAcc = temp; 
}

Account* GetNextAccount(Account* thisAccount) {
    return thisAccount -> nextAcc;
}

void DeleteAccount(Account* thisAccount, Account* head, Account* tail) {
    Account* currAcc = head;
    if ((thisAccount == head) && (thisAccount == tail)) {
        head = NULL;
        tail = NULL;
    } else if (thisAccount == head) {
        head = head->nextAcc;
    } else if (thisAccount == tail) {
        while (currAcc->nextAcc != thisAccount) {
            currAcc = currAcc->nextAcc;
        }
        currAcc->nextAcc = NULL;
        tail = currAcc;
    } else {
       while (currAcc->nextAcc != thisAccount) {
            currAcc = currAcc->nextAcc;
        }
        currAcc->nextAcc = thisAccount->nextAcc;
    }
    free(thisAccount);
}