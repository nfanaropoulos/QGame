#include <stdio.h>
#include <stdlib.h>
//Structure of the account form that will be saved in the accounts.txt file
struct account {
   char username[20];  //define of the string username with 20 maximum characters
   char password[20];  //define of the string password with 20 maximum characters
};
void account_create(void)
{
  char username[20];  //variable for the username given by the player
  char password[20];  //variable for the pasword given by the player
//  char acc.name[20];  //variable for the username that will be stored into the acccounts.txt file
//  char acc.password[20]; //variable for the password that will be stored into the accounts.txt file
  int acc_size ;  //variable for the size of each account

  system("CLS");
  printf("***Account Creation Page\n");
  printf("Please give me your Username (max 20 characters): ");
  scanf("%s", &username);
  printf("Please give me your password (max 20 characters: ");
  scanf("%s", &password);
  printf("Thank You. Your account has been created\n");

  struct account acc;  //Making structure as variable

  FILE *accounts;

  accounts = fopen ("accounts.txt", "rb+"); //Open the file accounts.txt in a read and right mode
  if(accounts == NULL){
    accounts = fopen ("accounts.txt", "wb+"); //if the file accounts.txt is not available  it's being created and opened in write and binary mode
  if(accounts == NULL){
      printf("Cannot open the file");
      exit(1);
  }
  }
  acc_size = sizeof(acc);

  fseek(accounts, 0, SEEK_END);   //searching the file accounts.txt and places the pointer at the end of the file
  fprintf(accounts, "%s %s\n", username, password); //write in accounts.txt the account entry
}
