# include <stdio.h>
# include <conio.h>
# include <string.h>
# include <stdlib.h>
# include <windows.h>
# include "var.h"
# include <shellApi.h>
# define CLEAR(x) memset(x,'\0',1000)                                                             //Found on Internet after long research on how to clear array memory.

void mainmenu(void);                                                                              //Function for mainmenu.
void logged(void);                                                                                //Function for logged.
void header(void);                                                                                //Function for header.
void adminlog(void);                                                                              //Function for adminlog.


//Global Variables
FILE *ckfile;                                                                                     //*********************************************TEST QUESTION CHECK FILE.
FILE *acc;                                                                                        //Pointer for the file of the accounts.dat which holds the account details of the players.
FILE *board;                                                                                      //Pointer for the file of board.dat which holds the scores of the players.
FILE *eq;                                                                                         //Pointer for the file of easy_questions.dat (eq being the initiates) which holds the questions of the game.
char uname[15];                                                                                   //Variable for the player input when they log in to their account. It's used to compare the input with the saved entry.
char upass[15];                                                                                   //Variable for the player input when they log in to their account. It's used to compare the input with the saved entry.
char digs;                                                                                        //Variable for the digits of Player's password.
int tmplives;                                                                                     //Variable to calculate the temporary lives of the player (used when the player gives a wrong answer).
long int recsize = sizeof(player);                                                                //Variable that is set to be long (accounts file can be long).
int tmpscore = 0;                                                                                 //Set's the temporary score (session score) back to 0.
int qnum;                                                                                         //Variable for the total number of questions inside the easy_questions.dat file.
char digs1;                                                                                       //Variable needed for masking the password when the player try to login.

void footer(){                                                                                    //Function for footer in game.
          gotoxy(1,65);
          printf("\033[1;34m");
          printf("********************************************************************************************************************************************************************************************************************************************");
          gotoxy(1,71);
          printf("Ver : 0.4 BETA");
          gotoxy(105,71);
          printf("IIEK AKMI 1st Semester");
          gotoxy(205,71);
          printf("Developer:Nikos Fanaropoulos");
          printf("\033[0m");
}

void header(){
                acc=fopen("data/accounts.dat","rb");
                system("CLS");                                                                     //Header for the logged menu.
                gotoxy(1,1);                                                                       //
                printf("\033[1;34m");                                                              //
                printf("Welcome ");                                                                //
                printf("\033[1;31m");                                                              //
                printf("%s", player.username);                                                     //
                printf("\033[0m");                                                                 //
                gotoxy(20,1);                                                                      //
                printf("\033[1;34m");                                                              //
                printf("Your Lives: ");                                                            //
                printf("\033[1;31m");                                                              //
                tmplives = player.lives;                                                           //Updater for lives (Needs further testing).
                printf("%d", tmplives);                                                            //
                printf("\033[0m");                                                                 //
                gotoxy(40,1);                                                                      //
                printf("\033[1;34m");                                                              //
                printf("Your Account Score: ");                                                    //
                printf("\033[1;31m");                                                              //
                printf("%d", player.score);                                                        //
                printf("\033[0m");                                                                 //
                gotoxy(70,1);                                                                      //
                printf("\033[1;34m");                                                              //
                printf("Your Session Score: ");                                                    //
                printf("\033[1;31m");                                                              //
                printf("%d", tmpscore);                                                            //
                printf("\033[0m");                                                                 //
                gotoxy(100,1);                                                                     //
                printf("\033[1;34m");                                                              //
                printf("Your Gold: ");                                                             //
                printf("\033[1;31m");                                                              //
                printf("%d", player.gold);                                                         //
                printf("\033[0m");                                                                 //
                printf("\033[1;34m");                                                              //
}
void fullscreen(){                                                                                //Function for full screen when the game opens. Code found on Internet.
keybd_event(VK_MENU,0x38,0,0);
keybd_event(VK_RETURN,0x1c,0,0);
keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

void gotoxy(int x,int y){                                                                         //Function to cursor allocation used for output and input data. Code found on Internet.

printf("%c[%d;%df",0x1B,y,x);
}

void view_debug(const char* pszFileName){                                                         //Not sure if it's gonna be needed yet.
    ShellExecuteA(GetDesktopWindow(),"open",pszFileName,NULL,NULL,SW_SHOW);
}
int question_increment(){                                                                         //Function used to calculate the random question each time.
        FILE *eq;                                                                                 //Declaration of pointer for the file containing the questions.
        e.id = 0;                                                                                 //Variable e.id is being reset to 0.
        struct easy e2;
        eq = fopen("data/easy_questions.txt", "rb+");                                             //Open the file easy_questions.dat in read and binary with append mode.
        while(fread(&e2, sizeof(e2), 1, eq)==1) {                                                   //While loop to read inside the questions file all question entries made by the administrator.
        e.id = e.id + 1;                                                                          //Set the value of the e.id variable to e.id +  1. The + 1 is needed to eliminate the 0 count.
        }
        fclose(eq);
        return e.id -1;                                                                              //Returns the value of e.id and save it in memory.
}

void mainmenu(){
        int ch;                                                                                   //Variable for the Create Account input choice.
        system("CLS");                                                                            //Calling the footer function.
        footer();
        gotoxy(108,20);                                                                           //Ansi code for coloring text. Same for all other cases.
        printf("\033[1;34m");
        printf("Main Menu");
        gotoxy(100,27);
        printf("1. Create Account.");
        gotoxy(100,28);
        printf("2. Log in.");
        gotoxy(100,29);
        printf("3. Exit.");
        gotoxy(100,32);
        printf("\033[1;32m");
        printf("Please choose 1 or 2:-> ");
        printf("\033[0m");
//      view_debug("12.bat");
        PlaySound(TEXT("Sounds/lounge.wav"), NULL, SND_LOOP | SND_ASYNC);                          //Play the song lounge.wav in a loop.
        printf("\033[1;31m");
        scanf("%d",&ch);                                                                           //Player input to choose if he want to create account or to login to an existent one.
        PlaySound(TEXT("Sounds/silent.wav"), NULL, SND_LOOP | SND_ASYNC);                          //Play the silent song to make lounge.wav stop. This is a patent since PlaySound function has no stop feature.
        memset(player.password, 0, sizeof player.password);                                        //Resets the player.password buffer memory.
        while(ch > 3 && ch <11297 || ch < 1 || ch > 11299){                                        //While loop that handles the player's input choice.
            fflush(stdin);                                                                         //Command to empty (flush) the stdin (standard input).
             MessageBox(0, "Please use 1 or 2 only!", "WARNING", 0);                               //Message box that appears when the player gives wrong choices. Choices adjusted for admin.
             mainmenu();                                                                           //Brings the player back to Main Menu in case of a wrong choice.
           }
        switch(ch)                                                                                 //Switch for the player choice.
        {
            case 1:                                                                                //First case : This choice is for Account Creation.
                      acc=fopen("data/accounts.dat","ab");                                         //Opens the accounts.dat in append/binary mode).
                      system("CLS");                                                               //Clear screen.
                      footer();                                                                    //Function to bring the footer text.
                      gotoxy(108,20);
                      printf("\033[1;34m");
                      printf("ACCOUNT CREATION");                                                  //Account Creation Menu Below.
                      gotoxy(100,24);                                                              //
                      printf("ENTER USERNAME:->");                                                 //
                      printf("\033[1;31m");                                                        //
                      scanf("%s", &player.username);                                               //Player input for username and saves the string given as player.username.
                      printf("\033[0m");                                                           //
                      fflush(stdin);                                                               //Empty the stdin
                      gotoxy(100,26);                                                              //
                      printf("\033[1;34m");                                                        //
                      printf("ENTER PASSWORD:->");                                                 //
                      printf("\033[1;31m");                                                        //
                      do{                                                                          //Simple loop for masking password entry with asterisks (*).
                        player.password[digs]=getch();                                             //Set's with each loop each single digit of player.password to be equal with the corresponding getch() input from player.
                        if(player.password[digs]=='\r')                                            //If the player hits Enter.
                        {
                           break;                                                                  //Breaks the loop.
                        }
                        if(player.password[digs] == 8)                                             //If the player decides to use backspace to correct his password . The ASCII code for backspace has been found on Internet.
                        {
                            putch('\b');                                                           //Use a soft (without deleting) backspace moving one digit back.
                            putch(NULL);                                                           //Replace the entry character with nothing (NULL).
                            putch('\b');                                                           //Move back again one space to the character that has been nulled.
                            digs--;                                                                //Remove one of the digs.
                            continue;
                        }
                        putch('*');                                                                //Put on screen the asterisk (*) instead of the key the player enters.
                        digs++;                                                                    //At the end of the loop, raise the next dig by one.
                      }
                      while(player.password[digs]!='\r');                                          //The loop goes on if the player does not hit Enter.
                      player.password[digs]='\0';                                                  //This is the finished player.password after the loop ends.
                      printf("\033[0m");                                                           //
                      player.score = 0;                                                            //Set's the score of the player to 0, since it's a new account that has been created.
                      player.gold = 0;                                                             //Set's the gold of the player to 0, since it's a new account that has been created.
                      player.lives = 3;                                                            //Set's the lives of the player to 3, which is the default amount for new accounts.
                      tmplives = 3;                                                                //Set's the temporary lives of the player to the default 3. Needed for in game calculation.
                      fseek(acc, 0, SEEK_END);                                                     //Goes to the end of the file accounts.dat that has been opened in line 125.
                      fwrite(&player,recsize,1,acc);                                               //Write's the input data from the player plus the fixed variables as a new entry in accounts.dat.
                      fflush(stdin);                                                               //Empty the stdin from the values given before.
                      fclose(acc);                                                                 //Close the file accounts.dat.
                      mainmenu();                                                                  //Brings the player back to Main Menu.
                    break;                                                                         //End of the first Case.
            case 2:                                                                                //Second Case : This choice is for Account Login.
                    acc=fopen("data/accounts.dat","rb");                                           //Opens the accounts.at in read/binary mode).
                    system("CLS");                                                                 //Clear screen.
                    footer();                                                                      //Call the footer function.
                    gotoxy(108,20);                                                                //
                    printf("\033[1;34m");                                                          //
                    printf("ACCOUNT LOGIN");                                                       //
                    gotoxy(100,24);                                                                //
                    printf("USERNAME:->");                                                         //
                    printf("\033[1;31m");                                                          //
                    scanf("%s", &uname);                                                           //Player input for username. This variable is different than the one we use in account creation because it's needed for comparison.
                    printf("\033[1;34m");                                                          //
                    gotoxy(100,25);                                                                //
                    printf("PASSWORD:->");                                                         //
                    printf("\033[1;31m");                                                          //Player input for password. This variable is different than the one we use in account creation because it's needed for comparison.
                      do{                                                                          //Same routine for masking the password when the player tries to login.
                        upass[digs1]=getch();                                                      //
                        if('\r'==upass[digs1])                                                     //
                        {
                             break;
                        }
                                                                                                   //
                        if(upass[digs1] == 8)                                                      //If the player decides to use backspace to correct his password . The ASCII code for backspace has been found on Internet.
                        {
                            putch('\b');                                                           //Use a soft (without deleting) backspace moving one digit back.
                            putch(NULL);                                                           //Replace the entry character with nothing (NULL).
                            putch('\b');                                                           //Move back again one space to the character that has been nulled.
                            digs1--;                                                               //Remove one of the digs1.
                            continue;
                        }
                        putch('*');                                                                //
                        digs1++;                                                                   //
                      }                                                                            //
                      while(upass[digs1]!='\r');                                                   //
                      upass[digs1]='\0';                                                           //
                    while(fread(&player,recsize,1,acc))                                            //While loop that reads the accounts.dat file one account (username, password etc) each time.
                    {
                        if(strcmp(uname,player.username)==0)                                       //If the login username string and the username entered at the account creation return 0 (are the same).
                        {
                            if(strcmp(upass,player.password)==0)                                   //And if the login password string and the password entered at the account creation return 0 (are the same).
                            {
                               tmplives = player.lives;                                            //Temporary lives variable gets the value of the saved lives for the account that is logged.
                               logged();                                                           //Calls on logged Function.
                            }
                            else {                                                                 //In case the password does not match with the one that was used in the account creation.
                                gotoxy(90,29);                                                     //
                                printf("\033[1;34m");                                              //
                                printf("Wrong Password Please Try Again!Press any key");           //Print that the password is wrong.
                                getch();                                                           //Wait for a key to be pressed by the player.
                                mainmenu();                                                        //Calls on mainmenu Function.
                                 }
                        }
                    }
                    gotoxy(90,29);                                                                 //
                    printf("\033[1;34m");                                                          //
                    printf("Account not found! Please press any key");                             //In case the username does not match with the one that was used in the account creation, print that the account is not found.
                    getch();                                                                       //Wait for a key to be pressed by the player.
                    mainmenu();                                                                    //Calls on mainmenu Function.
                    break;                                                                         //End of the second Case.
            case 3:
                exit(0);

            case 11298:                                                                            //11298 Case : This choice is for the Administrator Account. Workaround for super user rights.
                    adminlog();                                                                    //Calls on adminlog Function.
        }

}

void logged(){
    int ch1;                                                                                       //Variable for the Login Account input choice.
    int questionid;                                                                                //Variable for the question that is being currently asked from the game to the player.
    qnum = question_increment();                                                                   //Set's the total number of questions variable to be equal with the function that counts the entries.
    char continueq = 'y';                                                                          //Variable for asking the player if he wants to continue playing and have the game ask another question.
    char scorers[255];                                                                             //Variable with 255 maximum length needed to collect the data from the board.dat file for the high scores.
    int counter;                                                                                   //Variable needed to count how many tabs are needed when saving data for the leader board.
    int playerAnswer;                                                                              //Variable for the player input when he wants to give the answer of the question being asked by the game.
    int shopChoice;                                                                                //SHOP variable.
    int newScore;                                                                                  //variable to calculate new score . Needs more testing.
    footer();                                                                                      //Footer for the logged menu.
    header();                                                                                      //Header for the logged menu.
    gotoxy(100,22);                                                                                //
    printf("****Main Lobby****");                                                                  //
    gotoxy(100,24);                                                                                //
    printf("1. Play QUIZ");                                                                        //
    gotoxy(100,25);                                                                                //
    printf("2. LeaderBoard");                                                                      //
    gotoxy(100,26);                                                                                //
    printf("3. Shop");                                                                             //
    gotoxy(100,27);                                                                                //
    printf("4. Logout");                                                                           //
    PlaySound(TEXT("Sounds/lounge.wav"), NULL, SND_LOOP | SND_ASYNC);                              //Play the lounge.wav sound in a loop state.
    gotoxy(100,29);                                                                                //
    printf("\033[1;32m");                                                                          //
    printf("ENTER YOUR CHOICE:-> ");                                                               //
    printf("\033[1;31m");                                                                          //
    scanf("%d", &ch1);                                                                             //Input for player for his choice.
    PlaySound(TEXT("Sounds/silent.wav"), NULL, SND_LOOP | SND_ASYNC);                              //Play the silent song to make lounge.wav stop. This is a patent since PlaySound function has no stop feature.
        while(ch1 > 4 || ch1 < 1){                                                                 //While loop to make sure the player choose between 1 and 4.
          fflush(stdin);                                                                           //Clear stdin memory.
          MessageBox(0, "Please enter 1-2 or 3 only!", "Warning", 0);                              //Messagebox with the error message if the player choose something that is not valid.
          logged();                                                                                //Jump to logged label.
         }
    switch(ch1)                                                                                    //Switch for the player's choice.
      {
         case 1:                                                                                   //First Case. Player choose to play the Quiz Game.
            while (continueq == 'y'){                                                              //While loop that sets the variable continueq (if the player wants to continue playing after answering previous one) to 'y'.
               if(tmplives < 1)                                                                    //Condition for leaving the loop of asking question is if the player has less than 1 lives.
                 {
                   acc=fopen("data/accounts.dat","rb+");                                           //If player reach 0 lives, opens the accounts.dat file in read, binary and append mode.
                   rewind(acc);                                                                    //Sets the cursor to the beginning of the file accounts.dat.
                   while(fread(&player, recsize,1,acc)==1)                                         //While loop that reads the accounts.dat file one account per time.
                     {
                        if(strcmp(uname,player.username)==0)                                       //Comparing the username given by the player at the login with the username saved at the account creation and if found match.
                          {
                             newScore = player.score + tmpscore;                                   //Intermediate variable NewScore that is needed for the final player.score saved in accounts.dat. Equals old player.score plus tmpscore.
                             player.score = newScore;                                              //Sets the player.score that will be saved in the accounts.dat for the player to be equal with the newScore.
                             player.gold = player.score/100;                                       //Edit the player.gold amount saved in the file to be equal with 1/100 of the total player.score.
                             player.lives = tmplives;                                              //Update the player.lives in accounts.dat by making them equal with the new status tmplives this way players with 0 lives can't play more.
                             fseek(acc, -recsize,SEEK_CUR);                                        //Sets the cursor to the beginning of the player account entry by moving backwards exactly the same characters to rewrite new data.
                             fwrite(&player, recsize, 1, acc);                                     //Updates the account details for the player.
                             fclose(acc);                                                          //Closes the file accounts.dat .
                             fflush(stdin);                                                        //Clear memory of stdin.
                             tmpscore = 0;                                                         //Reset the tmpscore back to 0 after you stop playing so that when you start over again the tmpscore is 0 again.
                            }
                     }
                    PlaySound(TEXT("Sounds/ending.wav"), NULL, SND_LOOP | SND_ASYNC);              //Play the sound ending.wav when the player lose all his lives.
                    gotoxy(70,55);
                    printf("Sorry but you have no more lives to play the game. Press Any key");    //Game Over Message.
                    getch();                                                                       //Any key to Continue to get back to logged.
                    PlaySound(TEXT("Sounds/silent.wav"), NULL, SND_LOOP | SND_ASYNC);              //Ending the music.
                    logged();                                                                      //Calls the function logged.
                  }
                      srand ( time(NULL) );                                                        //Initialize random Number Generator.
                      questionid = rand() %(qnum-1) + 1;                                           //Set's the questionid variable to the random number between 0 and the remainder of (qnum - 1) and plus one.
                      eq=fopen("data/easy_questions.txt", "rb");                                   //Open's the file easy_questions.dat in reading and binary mode.
                      fseek(eq, 0, SEEK_SET);                                                      //Set's the file position of easy_questions.dat to the beginning of the file.
                      ckfile = fopen("data/check_questions.txt", "ab");                            //*********************************************TEST QUESTION CHECK FILE.
                      fseek(ckfile, 0, SEEK_SET);                                                  //*********************************************TEST QUESTION CHECK FILE.
                      ck.id = e.id;                                                                //*********************************************TEST QUESTION CHECK FILE.
                      fprintf(ckfile,"%d\n", ck.id);                                               //*********************************************TEST QUESTION CHECK FILE.
                      while(fread(&e, sizeof(e), 1, eq))                                           //While loop that read the file easy_questions.dat one entry at time.
                      {
                      if (questionid == e.id && questionid != ck.id)                               //If there is a match of questionid and the id of a line (question) in the easy_questions.dat file.
                        {
                            footer();                                                              //Set's the footer.
                            header();                                                              //Set's the header.
                      PlaySound(TEXT("Sounds/enxiety1.wav"), NULL, SND_LOOP | SND_ASYNC);          //Play the enxiety.wav sound in a loop for the player until he choose his answer.
                      gotoxy(70,25);
                      printf("\033[1;34m");
                      printf("QUESTION-->");
                      puts(e.question);                                                            //Places the question to the screen.
                      gotoxy(70,28);
                      printf("\033[1;33m");
                      printf("1) %s", e.answerA);                                                  //Places the first answer option to the screen.
                      gotoxy(70,30);
                      printf("2) %s", e.answerB);                                                  //Places the second answer option to the screen.
                      gotoxy(70,32);
                      printf("3) %s", e.answerC);                                                  //Places the third answer option to the screen.
                      gotoxy(70,34);
                      printf("4) %s", e.answerD);                                                  //Places the forth answer option to the screen.
                      fflush(stdin);                                                               //Clearing the stdin memory.
                      gotoxy(70,36);                                                               //
                      printf("\033[1;34m");                                                        //
                      printf("**************");                                                    //
                      gotoxy(70,38);                                                               //
                      printf("Your Choice (1-4) : ");                                              //
                      printf("\033[1;31m");                                                        //
                      playerAnswer = getchar();                                                    //Set's the player answer given by getchar (1-4).
                      while((char)playerAnswer> '4' || (char)playerAnswer <'1'){                   //While loop for character input, accepts only 1-4 (possible answers).
                        fflush(stdin);                                                             //Cleans up stdin memory.
                        MessageBox(0, "Please Enter 1-2-3 or 4 only !!", "Warning", 0);            //Message box if a wrong entry is being given.
                        playerAnswer = getchar();                                                  //Sets back the playeranswer variable to be the player's input (getchar).
                        }                                                                          //

                      if(playerAnswer == e.correct){                                               //If playeranswer equals the correct answer saved in easy_questions.dat.
                        PlaySound(TEXT("Sounds/correct.wav"), NULL, SND_ASYNC);                    //Play the sound "Correct.wat" once.
                        printf("\033[1;34m");                                                      //
                        gotoxy(70,50);                                                             //
                        printf("***************");                                                 //
                        gotoxy(70,51);                                                             //
                        printf("Correct Answer!");                                                 //
                        gotoxy(70,52);                                                             //
                        printf("***************");                                                 //
                        tmpscore += 5;                                                             //Adds to the score 5 points.
                        player.gold = player.score/100;                                            //Each 100 points give  1 Gold to the player.
//                      ck.id = e.id;                                                              //*********************************************TEST QUESTION CHECK FILE.
//                      fprintf(ckfile,"%d\n", ck.id);                                             //*********************************************TEST QUESTION CHECK FILE.
                        fclose(ckfile);                                                            //*********************************************TEST QUESTION CHECK FILE.

                       break;                                                                      //
                      }else{                                                                       //If the playeranswer does not match the correct answer saved in easy_questions.dat.
                      ck.id = e.id;                                                                //*********************************************TEST QUESTION CHECK FILE.
                      fprintf(ckfile,"%d\n", ck.id);                                               //*********************************************TEST QUESTION CHECK FILE.
                      fclose(ckfile);                                                              //*********************************************TEST QUESTION CHECK FILE.
                      PlaySound(TEXT("Sounds/wrong.wav"), NULL, SND_ASYNC);                        //Plays the sound wrong.wav once if the player gives a wrong answer.
                        printf("\033[1;34m");                                                      //
                        gotoxy(70,50);                                                             //
                        printf("***************");                                                 //
                        gotoxy(70,51);                                                             //
                        printf("Wrong Answer!");                                                   //
                        gotoxy(70,52);                                                             //
                        printf("***************");                                                 //
                        tmplives -= 1;                                                             //Removes one life if the player gives a wrong answer.
                      }                                                                            //
                        }                                                                          //

                      }                                                                            //
                printf("\033[1;34m");                                                              //
                gotoxy(70,53);                                                                     //
                printf("Continue ? (y/n): ");                                                      //Asks the player if he wants to continue no matter if the question is right or wrong.
                printf("\033[1;31m");                                                              //
                continueq = getch();                                                               //Set's the continueq (continue question) to be the character the player hits.
                      }                                                                            //Gets out of the loop which means that the player did choose 'N'.
                continueq = 'y';                                                                   //Sets the continueq variable back to the default 'Y'.
                fclose(acc);                                                                       //Closing the accounts file.
                acc=fopen("data/accounts.dat", "rb+");                                             //Reopens the accounts file in a reading and binary mode but also with append possibility.
                rewind(acc);                                                                       //Rewinds the file to the beginning.
                while(fread(&player, recsize,1,acc)==1)                                            //While loop that reads the player entries of the accounts.dat file
                {                                                                                  //
                    if(strcmp(uname,player.username)==0)                                           //If the compare between the variables uname and player.username returns 0 (to be the same).
                    {                                                                              //
                        newScore = player.score + tmpscore;                                        //Sets the newScore (intermediate variable) to be equal with the player.score saved in the file + the tmpscore of the session.
                        player.score = newScore;                                                   //Sets the player.score to be equal with the newScore.
                        player.gold = player.score/100;                                            //Sets the player.gold to be the 1/100 of the new player.score.
                        player.lives = tmplives;                                                   //Sets the player.lives to bne equal with the tmplives (temporary lives). Updates the file with the current lives status.
                        fseek(acc, -recsize,SEEK_CUR);                                             //Set's the file position of accounts.dat to the beginning of the entry (by moving backwards the same spaces) of current entry.
                        fwrite(&player, recsize, 1, acc);                                          //Updates the entry in accounts.dat with the new data.
                        fclose(acc);                                                               //Closes the file accounts.dat.
                        fflush(stdin);                                                             //Clears the stdin memory.
                    }                                                                              //
                }                                                                                  //
                board=fopen("data/board.dat", "r+");                                               //Opens the file board.dat in a reading and append mode.
                footer();                                                                          //Calls the footer function.
                header();                                                                          //Calls the header function.
                gotoxy(75,22);                                                                     //
                printf("Give me your preferred name for Leader board: ");                          //Asks the player for the Board Name of his choice. It's Dev's choice to allow the player to use different names for leader board.
                printf("\033[1;31m");                                                              //
                scanf("%s", &b.name);                                                              //Collects the Leader Board name of player's choice.
                fflush(stdin);                                                                     //Clears the stdin memory.
                b.score = tmpscore;                                                                //Set's the board score variable (b.score) to be equal to the temporary (session) score of the player.
                fseek(board, 0, SEEK_END);                                                         //Set's the file position of boards.dat to the end of the file.
                fprintf(board, "%s", b.name);                                                      //First part of the file input which is the name.
                counter = 6 - strlen(b.name)/8;                                                    //Variable to count how many tabs should be placed. 6 (default wanted tabs) - the length of the name / 8 characters (default tab).
                while (counter > 0)                                                                //while loop to add the tabs in between the name and the score.
                {                                                                                  //
                    counter--;                                                                     //Each time a tab is printed , decrease by one.
                    fprintf(board, "\t");                                                          //Printed tab.
                }                                                                                  //
                fprintf(board, "%d\n", b.score);                                                   //Last part of the file input which is the score.
                fclose(board);                                                                     //Closes the board.dat file.

                      logged();                                                                    //Calls the logged function.

                case 2:                                                                            //Second Case. Player choose to see the Leader Board.
                    system("CLS");
                    PlaySound(TEXT("Sounds/champions.wav"), NULL, SND_LOOP | SND_ASYNC);           //Play in a loop the champions.wav file.
                    gotoxy(85,13);
                    printf("\033[1;34m");
                    printf("**************LEADERBOARD******************\n\n");                     //Title of the Menu.
                    board = fopen("data/board.dat", "r");                                          //Opens the file board.dat in a read mode.
                      while(fgets(scorers, 255, (FILE*) board))                                    //While loop that retrieves the whole data from the board.dat file and saves them in a 255 character buffer.
                        {
                            printf("\033[1;31m");
                            printf("\t\t\t\t\t\t\t\t\t\t%s", scorers);                             //Print to the player's screen with 10 tabs for each line the lines one by one from the saved data.

                        }
                    fclose(board);
                    gotoxy(170,30);
                    printf("\033[1;34m");
                    printf("Press any key to go back");
                    getch();
                    logged();
                case 3:                                                                           //SHOP implementation
                    footer();
                    header();
                    PlaySound(TEXT("Sounds/shop.wav"), NULL, SND_LOOP | SND_ASYNC);
                    gotoxy(70,20);
                    printf("\033[1;34m");
                    printf("$$$$$$$$$$$$$$$$$$$$-----SHOP-----$$$$$$$$$$$$$$$$$$$$");
                    gotoxy(70,22);
                    printf("\033[1;34m");
                    printf("Available Gold : ");
                    printf("\033[1;31m");
                    printf("%d", player.gold);
                    gotoxy(70,25);
                    printf("1) 1 Live = 1 gold");
                    gotoxy(70,33);
                    printf("2) Enter 0 to go back to Lobby.");
                    gotoxy(70,35);
                    printf("\033[1;32m");
                    printf("Please Select: ");
                    printf("\033[1;31m");
                    scanf("%d", &shopChoice);

                    while(shopChoice > 1 || shopChoice < 0){
                    fflush(stdin);
                    MessageBox(0, "Currently option 1 is only available", "Warning", 0);
                    break;
                    }
                    if (shopChoice == 0)
                    {
                        logged();
                    }
                    if(shopChoice == 1)
                    {
                        if(player.gold <1)
                        {
                            gotoxy(70,40);
                            printf("\033[1;34m");
                            printf("Sorry but you do not have enough gold to make the purchase.");
                            getch();
                            logged();
                        }
                    acc=fopen("data/accounts.dat", "rb+");
                    rewind(acc);
                    while(fread(&player, recsize,1,acc)==1)
                      {
                         if(strcmp(uname,player.username)==0)
                          {
                    player.gold = player.gold - 1;
                    player.score = player.score - 100;
                    player.lives = player.lives + 1;
                    gotoxy(70,40);
                    printf("\033[1;34m");
                    printf("Purchase completed!");
                    getch();
                    fseek(acc, -recsize, SEEK_CUR);
                    fwrite(&player, recsize, 1, acc);
                    fclose(acc);
                    logged();
                          }
                      }
                    }
                case 4:
                    {
                        CLEAR(upass);                                                                                   //Found on Internet after long research on how to clear array memory.
                        mainmenu();
                    }
                }
                logged();

}
void adminlog(){
                system("CLS");
                int ch2;                                                                                       //Variable for the Administrator input choice.
                char another = 'y';                                                                            //Variable for asking the administrator if he wants to add another question to the easy_questions.dat file.
                footer();
                gotoxy(1,1);
                printf("\033[1;34m");
                printf("Welcome ");
                printf("\033[1;31m");
                printf("\033[1;31m");
                printf("ADMIN ACCOUNT");
                printf("\033[0m");
                gotoxy(100,20);
                printf("\033[1;34m");
                printf("****Main Lobby**** ");
                gotoxy(100,23);
                printf("1. ADD QUIZ Easy Questions");
                gotoxy(100,24);
                printf("2. ADD QUIZ Normal Questions");
                gotoxy(100,25);
                printf("3. ADD QUIZ Hard Questions");
                gotoxy(100,26);
                PlaySound(TEXT("Sounds/lounge.wav"), NULL, SND_LOOP | SND_ASYNC);
                gotoxy(100,29);
                printf("\033[1;32m");
                printf("Please Select 1-3: ");
                printf("\033[1;31m");
                scanf("%d", &ch2);
                PlaySound(TEXT("Sounds/silent.wav"), NULL, SND_LOOP | SND_ASYNC);
                switch(ch2)
                {
                case 1:
                    while (another == 'y'){
                      qnum = question_increment();
                      e.id = qnum;
                      eq=fopen("data/easy_questions.txt","rb+");
                      system("CLS");
                      printf("ENTER Question No %d:", qnum);
                      fflush(stdin);
                      printf("\nENTER Question:->");
                      fflush(stdin);
                      gets(e.question);
                      printf("\nENTER Choice 1:->");
                      fflush(stdin);
                      gets(e.answerA);
                      printf("\nENTER Choice 2:->");
                      fflush(stdin);
                      gets(e.answerB);
                      printf("\nENTER Choice 3:->");
                      fflush(stdin);
                      gets(e.answerC);
                      printf("\nENTER Choice 4:->");
                      fflush(stdin);
                      gets(e.answerD);
                      printf("\nENTER Correct Answer:->");
                      scanf("%s", &e.correct);
                      fseek(eq, 0, SEEK_END);
                      fwrite(&e, sizeof(e), 1, eq);
                      printf("Question Added!");
                      fclose(eq);
                      printf("Add another ? (y/n):");
                      another = getche();
                    }
                      break;
               }
               return(0);
            }

int main(){
    SetConsoleOutputCP(CP_UTF8);                                                                   //****************Experimentation entry: Making Console UTF8 characters friendly.
    qnum = question_increment();
    fullscreen();                                                                                  //Runs the full screen function.
mainmenu();
}
