#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct Account_struct {
    char userName[20];
    char password[20];
    char eCC[30];
    struct Account_struct* nextAcc;
} Account;

void CreateAccount(Account* thisAccount, char userInit[], char passwordInit[], 
char CCInit[], Account* nextAcc);

Account* GetNextAccount(Account* thisAccount);

void InsertAccountAfter(Account* thisAccount, Account* newAccount);

void DeleteAccount(Account* thisAccount, Account* head, Account* tail);

#endif