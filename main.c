# include <stdio.h>
# include <conio.h>
# include <string.h>
# include <stdlib.h>
# include <windows.h>
# include "var.h"
# include <shellApi.h>

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
void fullscreen(){                                                                                //Function for full screen when the game opens.
keybd_event(VK_MENU,0x38,0,0);
keybd_event(VK_RETURN,0x1c,0,0);
keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

void gotoxy(int x,int y){                                                                         //Function to cursor allocation used for output and input data.

printf("%c[%d;%df",0x1B,y,x);
}

void view_debug(const char* pszFileName){                                                         //Not sure if it's gonna be needed yet.
    ShellExecuteA(GetDesktopWindow(),"open",pszFileName,NULL,NULL,SW_SHOW);
}
int question_increment(){                                                                         //Function used to calculate the random question each time.
        FILE *eq;                                                                                 //Declaration of pointer for the file containing the questions.
        e.id = 0;                                                                                 //Variable e.id is being reset to 0.
        eq = fopen("easy_questions.txt", "rb+");                                                  //Open the file easy_questions.txt in read and binary with append mode.
        while(fread(&e, sizeof(e), 1, eq)==1) {                                                   //While loop to read inside the questions file all question entries made by the administrator.
        e.id = e.id + 1;                                                                          //Set the value of the e.id variable to e.id +  1. The + 1 is needed to eliminate the 0 count.
        }
        return e.id;                                                                              //Returns the value of e.id and save it in memory.
}

int main(){
    SetConsoleOutputCP(CP_UTF8);                                                                   //****************Experimentation entry: Making Console UTF8 characters friendly.
    fullscreen();                                                                                  //Runs the full screen function.
    FILE *acc;                                                                                     //Pointer for the file of the accounts.txt which holds the account details of the players.
    FILE *eq;                                                                                      //Pointer for the file of easy_questions.txt (eq being the initiates) which holds the questions of the game.
    FILE *board;                                                                                   //Pointer for the file of board.txt which holds the scores of the players.
    char uname[15];                                                                                //Variable for the player input when they log in to their account. It's used to compare the input with the saved entry.
    char upass[15];                                                                                //Variable for the player input when they log in to their account. It's used to compare the input with the saved entry.
    int ch;                                                                                        //Variable for the Create Account input choice.
    int ch1;                                                                                       //Variable for the Login Account input choice.
    int ch2;                                                                                       //Variable for the Administrator input choice.
    int qnum;                                                                                      //Variable for the total number of questions inside the easy_questions.txt file.
    qnum = question_increment();                                                                   //Set's the total number of questions variable to be equal with the function that counts the entries.
    int questionid;                                                                                //Variable for the question that is being currently asked from the game to the player.
    char another = 'y';                                                                            //Variable for asking the administrator if he wants to add another question to the easy_questions.txt file.
    char continueq = 'y';                                                                          //Variable for asking the player if he wants to continue playing and have the game ask another question.
    int playerAnswer;                                                                              //Variable for the player input when he wants to give the answer of the question being asked by the game.
    long int recsize;                                                                              //Variable that is set to be long (accounts file can be long).
    recsize = sizeof(player);                                                                      //Set's the value of the recsize Variable to the total length of the player structure (Each entry).
    int tempgold;                                                                                  //****************SHOP needed variable ????? check it if it's needed or not.
    char scorers[255];                                                                              //Variable with 255 maximum length needed to collect the data from the board.txt file for the high scores.
    int tmpscore = 0;                                                                              //Set's the temporary score (session score) back to 0.
    int tmplives;                                                                                  //Variable to calculate the temporary lives of the player (used when the player gives a wrong answer).
    int x;                                                                                         //Variable for the x axis needed for the alignment of the inputs/outputs.
    int y;                                                                                         //Variable for the y axis needed for the alignment of the inputs/outputs.
    int newScore;                                                                                  //variable to calculate new score . Needs more testing.
    int lives;                                                                                     //Variable for the lives of the player (used to calculate the actual lives remaining).
    int shopChoice;                                                                                //SHOP variable.
    int counter;                                                                                   //Variable needed to count how many tabs are needed when saving data for the leader board.
    int len;
    char digs;                                                                                     //Variable for the digits of Player's password.
    char asterisk;                                                                                 //Variable for changing the password digit into asterisk.

//Main Menu
mainmenu:{
        system("CLS");                                                                             //Lines 99-111. Game User Interface options for better visualization
        footer();
        gotoxy(108,20);                                                                            //Ansi code for coloring text. Same for all other cases.
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
        PlaySound(TEXT("lounge.wav"), NULL, SND_LOOP | SND_ASYNC);                                 //Play the song lounge.wav in a loop.
        printf("\033[1;31m");
        scanf("%d",&ch);                                                                           //Player input to choose if he want to create account or to login to an existent one.
        PlaySound(TEXT("silent.wav"), NULL, SND_LOOP | SND_ASYNC);                                 //Play the silent song to make lounge.wav stop. This is a patent since PlaySound function has no stop feature.
        while(ch > 3 && ch <11297 || ch < 1 || ch > 11299){                                        //While loop that handles the player's input choice.
            fflush(stdin);                                                                         //Command to empty (flush) the stdin (standard input).
             MessageBox(0, "Please use 1 or 2 only!", "WARNING", 0);                               //Message box that appears when the player gives wrong choices. Choices adjusted for admin.
             goto mainmenu;                                                                        //Brings the player back to Main Menu in case of a wrong choice.
           }
        switch(ch)                                                                                 //Switch for the player choice.
        {
            case 1:                                                                                //First case : This choice is for Account Creation.
                      acc=fopen("accounts.txt","ab");                                              //Opens the accounts.txt in append/binary mode).
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
                      scanf("%s", &player.password);                                               //Player input for password and saves the string given as player.password.
//                      for (digs = 1; digs <= 15 ; digs++)                                        //Password shown as * characters at the register page. Starting from 1st digit until 15th adding 1 dig each time.
//                          {
//                              asterisk = getch();                                                //The variable asterisk becomes the character input by the player.
//                              if(asterisk == '\r')                                               //If the asterisk is the enter key.
//                                {
//                                  break;                                                         //Break the for loop and move to the end for saving the data.
//                                }
//                              player.password[digs] = asterisk;                                  //If the asterisk is not the enter key, each character of the desired password gets it's appropriate sequence place to save.
//                              asterisk = '*';                                                    //Convert the asterisk into the character *.
//                              printf("%c", asterisk);                                            //Once the real character is saved into the player.password variable to be saved, now show to the screen only the asterisk.
//                          }
                      printf("\033[0m");                                                           //
                      player.score = 0;                                                            //Set's the score of the player to 0, since it's a new account that has been created.
                      player.gold = 0;                                                             //Set's the gold of the player to 0, since it's a new account that has been created.
                      player.lives = 3;                                                            //Set's the lives of the player to 3, which is the default amount for new accounts.
                      tmplives = 3;                                                                //Set's the temporary lives of the player to the default 3. Needed for in game calculation.

                      fseek(acc, 0, SEEK_END);                                                     //Goes to the end of the file accounts.txt that has been opened in line 125.
                      fwrite(&player,recsize,1,acc);                                               //Write's the input data from the player plus the fixed variables as a new entry in accounts.txt.
                      fflush(stdin);                                                               //Empty the stdin from the values given before.
                      fclose(acc);                                                                 //Close the file accounts.txt.
                      goto mainmenu;                                                               //Brings the player back to Main Menu.
                    break;                                                                         //End of the first Case.
            case 2:                                                                                //Second Case : This choice is for Account Login.
                    acc=fopen("accounts.txt","rb");                                                //Opens the accounts.txt in read/binary mode).
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
                    scanf("%s", &upass);
//                  for (digs = 1; digs <= 15 ; digs++)                                            //Password shown as * characters at the register page. Starting from 1st digit until 15th adding 1 dig each time.
//                        {
//                            asterisk = getch();                                                  //The variable asterisk becomes the character input by the player.
//                            if(asterisk == '\r')                                                 //If the asterisk is the enter key.
//                              {
//                                break;                                                           //Break the for loop and move to the end for saving the data.
//                              }
//                            upass[digs] = asterisk;                                              //If the asterisk is not the enter key, each character of the desired password gets it's appropriate sequence place to save.
//                            asterisk = '*';                                                      //Convert the asterisk into the character *.
//                            printf("%c", asterisk);                                              //Once the real character is saved into the player.password variable to be saved, now show to the screen only the asterisk.
//                        }
//                        printf("%s", upass[digs]);
                    while(fread(&player,recsize,1,acc))                                            //While loop that reads the accounts.txt file one account (username, password etc) each time.
                    {
                        if(strcmp(uname,player.username)==0)                                       //If the login username string and the username entered at the account creation return 0 (are the same).
                        {
                            if(strcmp(upass,player.password)==0)                                   //And if the login password string and the password entered at the account creation return 0 (are the same).
                            {
                               tmplives = player.lives;                                            //Temporary lives variable gets the value of the saved lives for the account that is logged.
                               goto logged;                                                        //Jumps on logged label.
                            }
                            else {                                                                 //In case the password does not match with the one that was used in the account creation.
                                gotoxy(90,29);                                                     //
                                printf("\033[1;34m");                                              //
                                printf("Wrong Password Please Try Again!Press any key");           //Print that the password is wrong.
                                getch();                                                           //Wait for a key to be pressed by the player.
                                goto mainmenu;                                                     //Jump on the mainmenu label.
                                 }
                        }
                    }
                    gotoxy(90,29);                                                                 //
                    printf("\033[1;34m");                                                          //
                    printf("Account not found! Please press any key");                             //In case the username does not match with the one that was used in the account creation, print that the account is not found.
                    getch();                                                                       //Wait for a key to be pressed by the player.
                    goto mainmenu;                                                                 //Jumps on the mainmenu label.
                    break;                                                                         //End of the second Case.
            case 3:
                exit(0);

            case 11298:                                                                            //11298 Case : This choice is for the Administrator Account. Workaround for super user rights.
                    goto adminlog;                                                                 //Jump on the adminlog label.
        }
    }
//logged
 logged:{
                system("CLS");
                footer();
                gotoxy(1,1);
                printf("\033[1;34m");
                printf("Welcome ");
                printf("\033[1;31m");
                printf("%s", player.username);
                printf("\033[0m");
                gotoxy(20,1);
                printf("\033[1;34m");
                printf("Your Lives: ");
                printf("\033[1;31m");
                printf("%d", tmplives);
                printf("\033[0m");
                gotoxy(40,1);
                printf("\033[1;34m");
                printf("Your Account Score: ");
                printf("\033[1;31m");
                printf("%d", player.score);
                printf("\033[0m");
                gotoxy(70,1);
                printf("\033[1;34m");
                printf("Your Session Score: ");
                printf("\033[1;31m");
                printf("%d", tmpscore);
                printf("\033[0m");
                gotoxy(100,1);
                printf("\033[1;34m");
                printf("Your Gold: ");
                printf("\033[1;31m");
                printf("%d", player.gold);
                printf("\033[0m");
                printf("\033[1;34m");
                gotoxy(100,22);
                printf("****Main Lobby****");
                gotoxy(100,24);
                printf("1. Play QUIZ");
                gotoxy(100,25);
                printf("2. LeaderBoard");
                gotoxy(100,26);
                printf("3. Shop");
                gotoxy(100,27);
                printf("4. Logout");
                PlaySound(TEXT("lounge.wav"), NULL, SND_LOOP | SND_ASYNC);
                gotoxy(100,29);
                printf("\033[1;32m");
                printf("ENTER YOUR CHOICE:-> ");
                printf("\033[1;31m");
                scanf("%d", &ch1);
                PlaySound(TEXT("silent.wav"), NULL, SND_LOOP | SND_ASYNC);
                while(ch1 > 4 || ch1 < 1){
                      fflush(stdin);
                      MessageBox(0, "Please enter 1-2 or 3 only!", "Warning", 0);
                      goto logged;
                    }
                  switch(ch1)
                {
                case 1:
                      while (continueq == 'y'){
                            if(tmplives < 1)
                            {
                                acc=fopen("accounts.txt","rb+");
                                rewind(acc);
                                while(fread(&player, recsize,1,acc)==1)
                                    {
                                        if(strcmp(uname,player.username)==0)
                                            {
                                                newScore = player.score + tmpscore;
                                                player.score = newScore;
                                                player.gold = player.score/100;
                                                player.lives = tmplives;
                                                fseek(acc, -recsize,SEEK_CUR);
                                                fwrite(&player, recsize, 1, acc);
                                                fclose(acc);
                                                fflush(stdin);
                                                tmpscore = 0;                       //Reset the tmpscore back to 0 after you stop playing so that when you start over again the tmpscore is 0 again
                                            }
                                    }
                                PlaySound(TEXT("ending.wav"), NULL, SND_LOOP | SND_ASYNC);
                                gotoxy(70,55);
                                printf("Sorry but you have no more lives to play the game. Press Any key");
                                getch();
                                PlaySound(TEXT("silent.wav"), NULL, SND_LOOP | SND_ASYNC);
                                goto logged;
                            }
                      srand ( time(NULL) );
                      questionid = rand() %(qnum-1) + 1;
//                    int a = answer;
                      eq=fopen("easy_questions.txt", "rb");
                      fseek(eq, 0, SEEK_SET);
                      while(fread(&e, sizeof(e), 1, eq))
                      {

                      if (questionid == e.id)
                        {
                            system("CLS");
                            footer();
                            gotoxy(1,1);
                            printf("\033[1;34m");
                            printf("Welcome ");
                            printf("\033[1;31m");
                            printf("%s", player.username);
                            printf("\033[0m");
                            gotoxy(20,1);
                            printf("\033[1;34m");
                            printf("Your Lives: ");
                            printf("\033[1;31m");
                            printf("%d", tmplives);
                            printf("\033[0m");
                            gotoxy(40,1);
                            printf("\033[1;34m");
                            printf("Your Account Score: ");
                            printf("\033[1;31m");
                            printf("%d", player.score);
                            printf("\033[0m");
                            gotoxy(70,1);
                            printf("\033[1;34m");
                            printf("Your Session Score: ");
                            printf("\033[1;31m");
                            printf("%d", tmpscore);
                            printf("\033[0m");
                            gotoxy(100,1);
                            printf("\033[1;34m");
                            printf("Your Gold: ");
                            printf("\033[1;31m");
                            printf("%d", player.gold);
                            printf("\033[0m");
                      PlaySound(TEXT("enxiety1.wav"), NULL, SND_LOOP | SND_ASYNC);

                      gotoxy(70,25);
                      printf("\033[1;34m");
                      printf("QUESTION-->");
                      puts(e.question);
                      gotoxy(70,28);
                      printf("\033[1;33m");
                      printf("1) %s", e.answerA);
                      gotoxy(70,30);
                      printf("2) %s", e.answerB);
                      gotoxy(70,32);
                      printf("3) %s", e.answerC);
                      gotoxy(70,34);
                      printf("4) %s", e.answerD);
                      fflush(stdin);
                      gotoxy(70,36);
                      printf("\033[1;34m");
                      printf("**************");
                      gotoxy(70,38);
                      printf("Your Choice (1-4) : ");
                      printf("\033[1;31m");
                      playerAnswer = getchar();
                      while((char)playerAnswer> '4' || (char)playerAnswer <'1'){
                        fflush(stdin);
                        MessageBox(0, "Please Enter 1-2-3 or 4 only !!", "Warning", 0);
                        playerAnswer = getchar();
                        }
                      if(playerAnswer == e.correct){
                        PlaySound(TEXT("correct.wav"), NULL, SND_ASYNC);
                        printf("\033[1;34m");
                        gotoxy(70,50);
                        printf("***************");
                        gotoxy(70,51);
                        printf("Correct Answer!");
                        gotoxy(70,52);
                        printf("***************");
                        tmpscore += 5;
 //                     player.score = tmpscore;                         //might need to uncomment
                        player.gold = player.score/100;
 //                     player.lives = tmplives;                         //might need to uncomment
                       break;
                      }else{
                      PlaySound(TEXT("wrong.wav"), NULL, SND_ASYNC);
                        printf("\033[1;34m");
                        gotoxy(70,50);
                        printf("***************");
                        gotoxy(70,51);
                        printf("Wrong Answer!");
                        gotoxy(70,52);
                        printf("***************");
                        tmplives -= 1;
                      }
                        }
                      }
                printf("\033[1;34m");
                gotoxy(70,53);
                printf("Continue ? (y/n): ");
                printf("\033[1;31m");
                continueq = getch();
                      }
                continueq = 'y';
                fclose(acc);
                acc=fopen("accounts.txt", "rb+");
                rewind(acc);
                while(fread(&player, recsize,1,acc)==1)
                {
                    if(strcmp(uname,player.username)==0)
                    {
                        newScore = player.score + tmpscore;
                        player.score = newScore;
                        player.gold = player.score/100;
                        player.lives = tmplives;
                        fseek(acc, -recsize,SEEK_CUR);
                        fwrite(&player, recsize, 1, acc);
                        fclose(acc);
                        fflush(stdin);
                    }
                }
                board=fopen("board.txt", "r+");
                system("CLS");
                footer();
                gotoxy(1,1);
                printf("\033[1;34m");
                printf("Welcome ");
                printf("\033[1;31m");
                printf("%s", player.username);
                printf("\033[0m");
                gotoxy(20,1);
                printf("\033[1;34m");
                printf("Your Lives: ");
                printf("\033[1;31m");
                printf("%d", tmplives);
                printf("\033[0m");
                gotoxy(40,1);
                printf("\033[1;34m");
                printf("Your Account Score: ");
                printf("\033[1;31m");
                printf("%d", player.score);
                printf("\033[0m");
                gotoxy(70,1);
                printf("\033[1;34m");
                printf("Your Session Score: ");
                printf("\033[1;31m");
                printf("%d", tmpscore);
                printf("\033[0m");
                gotoxy(100,1);
                printf("\033[1;34m");
                printf("Your Gold: ");
                printf("\033[1;31m");
                printf("%d", player.gold);
                printf("\033[0m");
                printf("\033[1;34m");
                gotoxy(75,22);
                printf("Give me your preferred name for Leader board: ");
                printf("\033[1;31m");
                scanf("%s", &b.name);
                fflush(stdin);
                b.score = tmpscore;
                fseek(board, 0, SEEK_END);
                fprintf(board, "%s", b.name);                                               //First part of the file input which is the name.
                counter = 6 - strlen(b.name)/8;                                             //Variable to count how many tabs should be placed. 6 (default wanted tabs) - the length of the name / 8 characters (default tab).
                while (counter > 0)                                                         //while loop to add the tabs in between the name and the score.
                {
                    counter--;                                                              //Each time a tab is printed , decrease by one.
                    fprintf(board, "\t");                                                   //Printed tab.
                }
                fprintf(board, "%d\n", b.score);                                            //Last part of the file input which is the score.
                fclose(board);

                      goto logged;

                case 2:
                    system("CLS");
                    PlaySound(TEXT("champions.wav"), NULL, SND_LOOP | SND_ASYNC);
                    gotoxy(85,13);
                    printf("\033[1;34m");
                    printf("**************LEADERBOARD******************\n\n");
                    board = fopen("board.txt", "r");
                      while(fgets(scorers, 255, (FILE*) board))
                        {
                            printf("\033[1;31m");
                            printf("\t\t\t\t\t\t\t\t\t\t%s", scorers);

                        }
                    fclose(board);
                    gotoxy(170,30);
                    printf("\033[1;34m");
                    printf("Press any key to go back");
                    getch();
                    goto logged;
                case 3:                                                                           //SHOP implementation
                    system("CLS");
                    footer();
                    PlaySound(TEXT("shop.wav"), NULL, SND_LOOP | SND_ASYNC);
                    gotoxy(1,1);
                    printf("\033[1;34m");
                    printf("Welcome ");
                    printf("\033[1;31m");
                    printf("%s", player.username);
                    printf("\033[0m");
                    gotoxy(20,1);
                    printf("\033[1;34m");
                    printf("Your Lives: ");
                    printf("\033[1;31m");
                    printf("%d", tmplives);
                    printf("\033[0m");
                    gotoxy(40,1);
                    printf("\033[1;34m");
                    printf("Your Account Score: ");
                    printf("\033[1;31m");
                    printf("%d", player.score);
                    printf("\033[0m");
                    gotoxy(70,1);
                    printf("\033[1;34m");
                    printf("Your Session Score: ");
                    printf("\033[1;31m");
                    printf("%d", tmpscore);
                    printf("\033[0m");
                    gotoxy(100,1);
                    printf("\033[1;34m");
                    printf("Your Gold: ");
                    printf("\033[1;31m");
                    printf("%d", player.gold);
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
                        goto logged;
                    }
                    if(shopChoice == 1)
                    {
                        if(player.gold <1)
                        {
                            gotoxy(70,40);
                            printf("\033[1;34m");
                            printf("Sorry but you do not have enough gold to make the purchase.");
                            getch();
                            goto logged;
                        }
                    acc=fopen("accounts.txt", "rb+");
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
                    goto logged;
                          }
                      }
                    }
                case 4:
                    {
                        goto mainmenu;
                    }
                }
                goto logged;

           }
//Administrator Log in
 adminlog:{
                system("CLS");
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
                PlaySound(TEXT("lounge.wav"), NULL, SND_LOOP | SND_ASYNC);
                gotoxy(100,29);
                printf("\033[1;32m");
                printf("Please Select 1-3: ");
                printf("\033[1;31m");
                scanf("%d", &ch2);
                PlaySound(TEXT("silent.wav"), NULL, SND_LOOP | SND_ASYNC);
                switch(ch2)
                {
                case 1:
                    while (another == 'y'){
                      qnum = question_increment();
                      e.id = qnum;
                      eq=fopen("easy_questions.txt","rb+");
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
}