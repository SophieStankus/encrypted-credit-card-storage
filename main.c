#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "Account.h"


// Can both encrypt and decrypt an inputted CC number via XOR & keys 
char* Encrypt(char arr[]) {
  char keys[17] = "aghedenjisajldsd";
  char keys2[17] = "paxgalzdsajyjslad";

  char* newInt = malloc(17 * sizeof(char));

  for (int i = 0; i < 16; i++) {
    char key = *(keys + i);
    char x = arr[i]^key;
    newInt[i] = x;
  }
  for (int i = 0; i < 16; i++) {
    char key = *(keys2 + i);
    char x = arr[i]^key;
    newInt[i] = x;
  }

  newInt[16] = '\0';

  return newInt;
}

char PrintFirstMenu() {
    char userChar;
    char valid[4] = {'1', '2', '3'};
    bool isValid = false;
    

    printf("OPTIONS:\n");
    printf("1. Sign into existing account\n");
    printf("2. Create new account\n");
    printf("3. Quit\n");
    printf("\nEnter the number of your choice:\n");

    while (!isValid) {
        scanf(" %c", &userChar);
        for (int i = 0; i < 3; i++) {
            if (userChar == valid[i]) {
                isValid = true;
                return userChar;
            } 
        }
         printf("\nEnter the number of your choice:\n");
    }
    return userChar;
}

Account* signInMenu(){
    char userName[20];
    char password[20];
    char CC[20] = "Temp";
    Account* acc;
    printf("SIGN IN TO EXISTING ACCOUNT\n");
    printf("Enter your username:\n");
    scanf("%s", userName);
    getchar();
    printf("Enter your password:\n");
    scanf("%s", password);
    getchar();
    acc = (Account*)malloc(sizeof(Account));
    assert(acc);
    CreateAccount(acc, userName, password, CC, NULL);
    return acc;
}

Account* createAccountMenu(){
    char userName[20];
    char password[20];
    char CC[40] = "No Credit Card.";
    Account* acc;
    printf("CREATE A NEW ACCOUNT\n");
    printf("Choose a username:\n");
    scanf("%s", userName);
    getchar();
    printf("Choose a password:\n");
    scanf("%s", password);
    getchar();
    acc = (Account*)malloc(sizeof(Account));
    assert(acc);
    CreateAccount(acc, userName, password, CC, NULL);
    return acc;
}

char mainMenu(Account* acc){
    char userChar;
    char valid[4] = {'1', '2', '3', '4'};
    bool isValid = false;
    
    printf("\nPlease select an option:\n");
    printf("1. Get credit card number\n");
    printf("2. Change credit card number\n");
    printf("3. Quit (Save Information)\n");
    printf("4. Delete Account\n");
    printf("\nEnter the number of your choice:\n");

    while (!isValid) {
        scanf(" %c", &userChar);
        for (int i = 0; i < 4; i++) {
            if (userChar == valid[i]) {
                isValid = true;
                return userChar;
            } 
            
        }
        printf("\nPlease make a valid selection:\n");
    }
    return userChar;

}

void changeCreditCard(Account* acc){
    char* CC = (char*)malloc(sizeof(char)*17);
    assert(CC);
    printf("Please enter your new credit card number (Must be 16 digits, no spaces):\n");
    while (strlen(CC) != 16) {
        scanf("%s", CC);
        getchar();
        if (strlen(CC) != 16) {
            printf("Your input was not 16 digits, please try again: \n");
        }
    }
    strcpy(acc->eCC, CC);
    free(CC);
    
}

int main(void) {

    Account* head = NULL;
    Account* tail = NULL;
    Account* currAcc = NULL;
    Account* tempAcc = NULL;
    
    //Reads in all accounts saved in UserInfo.txt and creates a linked list
    //information is read in 3 line blocks (username\n password\n credit card\n)
    char str[50];
    FILE *fp;
    fp = fopen("UserInfo.txt", "r");

    if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }


    while( fgets(str, 30, fp) != NULL )
    {
        char userName[40];
        strcpy(userName, str);
        strtok(userName, "\n");

        fgets(str, 30, fp);
        char password[40];
        strcpy(password, str);
        strtok(password, "\n");

        fgets(str, 30, fp);
        char CC[40];
        strcpy(CC, str);
        strtok(CC, "\n");

       if(head == NULL){
                head = (Account*)malloc(sizeof(Account)); // Front of nodes list
                assert(head);
                CreateAccount(head, userName, password, CC, NULL);
                tail = head;
        } else{
                currAcc = (Account*)malloc(sizeof(Account));
                assert(currAcc != NULL);
                CreateAccount(currAcc, userName, password, CC, NULL);
                InsertAccountAfter(tail, currAcc);
                tail = currAcc;
            }

    }
    fclose(fp);
    //end of creating linked list
    
                    //****PLACE ALL CODE TO RUN THE PROGRAM HERE*****
    char userChar = '0';
    // user wants to create new account
    while (userChar != '3') {
        userChar = PrintFirstMenu();
        if (userChar == '2') {
            Account* newAccount = createAccountMenu();
            changeCreditCard(newAccount);
            strcpy(newAccount->eCC, Encrypt(newAccount->eCC));
            if(head == NULL){
                head = newAccount;
                tail = head;
            } else{
                 InsertAccountAfter(tail, newAccount);
                 tail = newAccount;
            }

            //userChar = '1';
        } 


        // User wants to sign into existing account
        if (userChar == '1') {
            bool signedIn = false;
            while(signedIn == false){
                Account* newAccount = signInMenu();
                currAcc = head;
                while (currAcc != NULL) {
                    if (strcmp(currAcc->userName, newAccount->userName)==0 
                    && strcmp(currAcc->password, newAccount->password) ==0) {
                        signedIn = true;
                        printf("\nSigned in!\n");
                        break;
                    }
                    currAcc = currAcc->nextAcc;
                }
                if(signedIn == false ){
                    printf("\nInvalid username and/or password. Please try again.\n");
                }
                
            }
            
            bool doneMenu = false;
            while(doneMenu == false){
                userChar = mainMenu(currAcc);
                // User wants to get credit card 
                if (userChar == '1') {
                    printf("Your credit card number is: %s\n", Encrypt(currAcc->eCC));
                }

                // User wants to change credit card 
                if (userChar == '2') {
                    changeCreditCard(currAcc);
                    strcpy(currAcc->eCC, Encrypt(currAcc -> eCC));
                    printf("Credit card number changed.\n");
                }

                if(userChar == '3'){
                    doneMenu = true;
                }

                // User wants to delete account 
                if (userChar == '4') {
                    DeleteAccount(currAcc, head, tail);
                    printf("Account deleted\n");
                    userChar = '2';
                    doneMenu = true;
                }

            // If user wants to quit, userChar already is 3 & exit commands will be run
            }
        }
    } 

    

    // User wants to quit 
    if (userChar == '3') {
        //Writes all the information in linked list back into UserInfo.txt
        //Run this code when user selects the "Quit" option.
        fp = fopen("UserInfo.txt", "w");
        if(fp == NULL)
        {
            printf("Error opening file\n");
            exit(1);
        }

        currAcc = head;                
        while (currAcc!= NULL) {
            fprintf (fp, "%s\n", currAcc->userName);
            fprintf (fp, "%s\n", currAcc->password);
            fprintf (fp, "%s\n", currAcc->eCC);
            currAcc = GetNextAccount(currAcc);
        }
        fclose (fp);
        //end writing information into file
   
        //deallocate all heap memory
        currAcc = head;                
        while (currAcc!= NULL) {
            tempAcc = currAcc;
            currAcc = GetNextAccount(currAcc);
            free(tempAcc);
        }
        //end deallocation
    }

    return 0;
}