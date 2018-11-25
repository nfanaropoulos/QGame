#ifndef VAR_H_INCLUDED
#define VAR_H_INCLUDED
#endif // VAR_H_INCLUDED
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct p{
        char username[15];
        char password[15];
        int score;
        int gold;
        int lives;
};
struct easy{
        int id;
        char question[150];
        char answerA[30];
        char answerB[30];
        char answerC[30];
        char answerD[30];
        int correct;
};
struct board{
        char name[15];
        int score;
        };
struct p player;
struct easy e;
struct board b;
