//Problem:
/*
終極密碼
寫一個C程式，讓電腦隨機產生一個1~99間的數字，讓兩位玩家輪流
來猜。遊戲開始前先向使用者詢問是要與玩家對戰還是電腦對戰
遊戲開始後電腦首先提示此數字介於1~99。若玩家猜中此數字者則
為輸。若未猜中，則電腦以玩家猜的數字N為界，將提示縮小為1到
(N-1) 或(N+1)到99，再由下一位玩家(或電腦)來猜。猜的數字必須
位於提示範圍中。
不斷重複上述動作直到產生輸家後，電腦詢問玩家是否再玩。若要
再玩則重新開始遊戲。
注意：隨機產生的數字必須每次執行都要不一樣
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#pragma warning(disable:4996)
int answer;
int Max = 99, Min = 1;
int n, n2, choice;
bool HaHaPoint = false;

void game1();
void game2();
void initVar();
void displayTitle();
void strickRange(int);
void loseParty(const char*);
void displayRange();

int main() {
    srand((unsigned)time(NULL));
    while (!HaHaPoint) {
        displayTitle();
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            answer = rand() % 99 + 1;
            game1();
            break;
        case 2:
            answer = rand() % 99 + 1;
            game2();
            break;
        }
    }
    system("pause");
    return 0;
}


void displayTitle() {
    printf("Welcome to this game\n");
    printf("Playing with computer please press 1\n");
    printf("Playing with other player please press 2\n");
}

void displayRange() {
    if (Min != 1 && Max == 99)
        printf("The code is between %d and %d\n", Min - 1, Max);
    else if (Min == 1 && Max != 99)
        printf("The code is between %d and %d\n", Min, Max + 1);
    else if (Min == 1 && Max == 99)
        printf("The code is between %d and %d\n", Min, Max);
    else
        printf("The code is between %d and %d\n", Min - 1, Max + 1);
}


void game1() {
    char exit;
    int comGuess;
    while (1) {
        displayRange();
        printf("Player0 input your guess\n");
        while (scanf("%d", &n)) {
            if ((n <= Max && n >= Min) || (Max == 99 && n <= Max && n >= Min) || (Min == 1 && n <= Max && n >= Min))
                break;
            else {
                printf("Range error!\n");
                displayRange();
                printf("Player0 input your guess\n");
            }
        }
        if (n == answer) {
            //user lose
            const char *name = "Player0";
            loseParty(name);
            //printf("Bomb!! Player0 is dead!\n");
            printf("Try again <Y/N> ?\n");
            getchar();
            scanf("%c", &exit);
            if (exit == 'n' || exit == 'N') {
                HaHaPoint = true;
                break;
            }
            else if (exit == 'Y' || exit == 'y') {
                initVar();
                system("cls");
                break;
            }
            else
                break;
        }
        else
            strickRange(n);

        comGuess = rand() % (Max - Min) + Min + 1;
        printf("Computer guess %d\n", comGuess);
        if (comGuess == answer) {
            //computer lose
            const char *name = "computer";
            loseParty(name);
            //printf("Bomb!! computer is dead\n");
            printf("Try again <Y/N> ?\n");
            getchar();
            scanf("%c", &exit);
            if (exit == 'n' || exit == 'N') {
                HaHaPoint = true;
                break;
            }
            else if (exit == 'Y' || exit == 'y') {
                system("cls");
                initVar();
                break;
            }
            else
                break;
        }
        else
            strickRange(comGuess);
    }
}

void game2() {
    char exit;
    while (1) {
        displayRange();
        printf("Player0 input your guess\n");
        while (scanf("%d", &n)) {
            if ((n <= Max && n >= Min) || (Max == 99 && n <= Max && n >= Min) || (Min == 1 && n <= Max && n >= Min))
                break;
            else {
                printf("Range error!\n");
                displayRange();
                printf("Player0 input your guess\n");
            }
        }
        if (n == answer) {
            //user0 lose
            const char *name = "Player0";
            loseParty(name);
            //printf("Bomb!! Player0 is dead!\n");
            printf("Try again <Y/N> ?\n");
            getchar();
            scanf("%c", &exit);
            if (exit == 'n' || exit == 'N') {
                HaHaPoint = true;
                break;
            }
            else if (exit == 'Y' || exit == 'y') {
                initVar();
                system("cls");
                break;
            }
            else
                break;
        }
        else
            strickRange(n);

        displayRange();
        printf("Player1 input your guess\n");
        while (scanf("%d", &n2)) {
            if ((n2 <= Max && n2 >= Min) || (Max == 99 && n2 <= Max && n2 >= Min) || (Min == 1 && n2 <= Max && n2 >= Min))
                break;
            else {
                printf("Range error!\n");
                displayRange();
                printf("Player1 input your guess\n");
            }
        }
        if (n2 == answer) {
            //user1 lose
            const char *name = "Player1";
            loseParty(name);
            //printf("Bomb!! Player1 is dead!\n");
            printf("Try again <Y/N> ?\n");
            getchar();
            scanf("%c", &exit);
            if (exit == 'n' || exit == 'N') {
                HaHaPoint = true;
                break;
            }
            else if (exit == 'Y' || exit == 'y') {
                initVar();
                system("cls");
                break;
            }
            else
                break;
        }
        else
            strickRange(n2);
    }
}

void initVar() {
    Max = 99;
    Min = 1;
    answer = rand() % 99 + 1;
}

void strickRange(int input) {
    if (input <= Max && input >= answer)
        Max = input - 1;
    else
        Min = input + 1;
}

void loseParty(const char *id) {
    system("cls");
    for (int i = 0; i < 5; i++) {
        printf("\nBomb!! %s is\n", id);
        printf("XXXXX   XXXXXXX     X     XXXXX  \n");
        printf("X    X  X          X X    X    X \n");
        printf("X     X X         X   X   X     X\n");
        printf("X     X XXXXXXX  X     X  X     X\n");
        printf("X     X X        XXXXXXX  X     X\n");
        printf("X    X  X       X       X X    X \n");
        printf("XXXXX   XXXXXXX X       X XXXXX  \n\n");
        printf("%d     Password is %d", 5 - i, answer);
        Sleep(800);
        system("cls");
        Sleep(200);
    }
}
