# encrypted-credit-card-storage

Implementation Details:

This is an account structure that holds a username, password, and encrypted credit card number of a user. This was implemented in a linked list, so the account also has a pointer to the next account. 
The encryption method uses exclusive or and two keys the length of a credit card number to encrypt the number two times in for loops in the function. It uses XOR so that it is a reversible method, and it both encodes and decodes a credit card number.
The program includes functions for printing various user input menus, and most of its functionality is in the main method, which cycles through various methods in a while loop until the user chooses to terminate the program, and then all the information is written into a userinfo.txt file. When the program starts again, the information in the text file is converted into a linked list by reading each line.

Compilation Directions:

To compile in VSC:
Step 1: Make sure all files (including UserInfo.txt) are in the same folder and your terminal references that folder.
Step 2: gcc main.c Account.c
Step 3: ./a

User Manual:

- Compile and run main method in main.c file
- Enter 1 to log in to an existing account, 2 to create a new account, or 3 (at any menu) to quit. 
- If you create a new account, you’ll be prompted to enter a username, password, and credit card number (don’t worry, it’ll be encrypted!). You’ll then be logged out so that you can login again and access your account menu.
- Once you sign in, you’ll be able to delete your account, get your credit card information, or change your credit card number that is on file.
- Again, enter 3 at any menu to quit the program. Your information will be saved on termination of the program in an external text file (but confidential credit cards are encrypted)
