/*
//PlayerA WASD 左上方
//PlayerB IJKL 右下方
//中間的道具(#)可以把對手變小 碰到對手時可以ㄘ掉他 讓他回原點
*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<vector>
#include<math.h>
#define UP 'w'
#define LEFT 'a'
#define RIGHT 'd'
#define DOWN 's'
#define UP_ 'i'
#define LEFT_ 'j'
#define RIGHT_ 'l'
#define DOWN_ 'k'

void printMap();
void processA();
void processB();
void control();
void generateFood();
void overDisplay();
void resetStatus();
int GameOver();
void saveGameStatus();


//0 wall,1Route,2PlayerA,3PlayerB,4Food
int map[15][15] = { 
        { 0,2,0,0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,1,1,1,0,1,1,1,1,1,1,1,1,1,0 },
        { 0,1,0,1,0,1,0,0,1,0,0,0,0,1,0 },
        { 0,1,0,1,0,1,1,1,1,0,1,1,1,1,0 },
        { 0,1,0,1,0,0,0,0,1,1,1,0,0,0,0 },
        { 0,1,0,1,1,1,1,1,1,0,1,1,1,1,0 },
        { 0,1,0,1,0,0,0,0,1,0,0,0,0,1,0 },
        { 0,1,1,1,0,1,1,5,1,0,1,1,1,1,0 },
        { 0,0,0,1,0,1,0,0,0,0,1,0,0,1,0 },
        { 0,1,1,1,0,1,1,1,1,1,0,1,1,1,0 },
        { 0,1,0,0,0,0,1,0,0,1,0,0,0,1,0 },
        { 0,0,0,1,1,0,1,1,1,1,1,1,1,1,0 },
        { 0,1,0,0,1,0,0,1,0,0,0,0,0,0,0 },
        { 0,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
        { 0,0,0,0,0,0,0,0,0,0,0,0,0,3,0 } 
};
int ori_map[15][15] = {
    { 0,2,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,1,1,1,0,1,1,1,1,1,1,1,1,1,0 },
    { 0,1,0,1,0,1,0,0,1,0,0,0,0,1,0 },
    { 0,1,0,1,0,1,1,1,1,0,1,1,1,1,0 },
    { 0,1,0,1,0,0,0,0,1,1,1,0,0,0,0 },
    { 0,1,0,1,1,1,1,1,1,0,1,1,1,1,0 },
    { 0,1,0,1,0,0,0,0,1,0,0,0,0,1,0 },
    { 0,1,1,1,0,1,1,5,1,0,1,1,1,1,0 },
    { 0,0,0,1,0,1,0,0,0,0,1,0,0,1,0 },
    { 0,1,1,1,0,1,1,1,1,1,0,1,1,1,0 },
    { 0,1,0,0,0,0,1,0,0,1,0,0,0,1,0 },
    { 0,0,0,1,1,0,1,1,1,1,1,1,1,1,0 },
    { 0,1,0,0,1,0,0,1,0,0,0,0,0,0,0 },
    { 0,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,3,0 }
};
//A,B玩家移動方向
int dirPlayerA_X = 0;
int dirPlayerA_Y = 0;
int dirPlayerB_X = 0;
int dirPlayerB_Y = 0;
//Score
int ScoreA = 0;
int ScoreB = 0;
std::vector<int> route;
//item
int isPlayerAGhost = 0;
int isPlayerBGhost = 0;
//ghostCoolDown
int oriStepA = 0;
int oriStepB = 0;
//Steps of A and B Player
int stepA = 0;
int stepB = 0;

int numberOfFood = 11;
FILE *history = NULL;

struct list {
    char nme[10];
    int highScore;
};

int main() {
    
    int c;
    history = fopen("history.txt", "a");
    srand((unsigned)time(NULL));
    system("color 0B");
    generateFood();
    printMap(); //印地圖
    while (1) {
        //printMap(); //印地圖
        if (_kbhit()) {
            system("cls");
            control(); //玩家按鍵盤
            processA(); //移動陣列中玩家A的位置
            processB(); //移動陣列中玩家B的位置
            printMap();
        }
        if (isPlayerAGhost && (stepA - oriStepA > 20)){
            isPlayerAGhost = 0;
        }
        else if (isPlayerBGhost && (stepB - oriStepB > 20)) {
            isPlayerBGhost = 0;
        }
        
        if (GameOver()) {
            system("cls");
            overDisplay();
            printf("1. 再來啊\n2. 放我走\n");
            scanf("%d", &c);
            if (c == 1) {
                resetStatus();
                system("cls");              
                printMap();
                continue;
            }
            else {
                saveGameStatus();
                break;
            }
                
        }
        else continue;
    }
    system("pause");
    return 0;
}

void printMap() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (map[i][j] == 0)
                printf("█");
            else if (map[i][j] == 1)
                printf("　");
            else if (map[i][j] == 2 && !isPlayerAGhost) //PlayerA
                printf("Ｘ");
            else if (map[i][j] == 2 && isPlayerAGhost) //PlayerA
                printf("x ");
            else if (map[i][j] == 3 && !isPlayerBGhost) //PlayerB
                printf("Ｏ");
            else if (map[i][j] == 3 && isPlayerBGhost) //PlayerB
                printf("o ");
            else if (map[i][j] == 4)
                printf("＊");
            else if (map[i][j] == 5)
                printf("＃");
        }
        printf("\n");
    }
    printf("A Score:%d\tStep:%d\n", ScoreA, stepA);
    printf("B Scord:%d\tStep:%d\n", ScoreB, stepB);
    printf("PlayerA Control:w(UP) a(LEFT) s(DOWN) d(RIGHT)\n");
    printf("PlayerB Control:i(UP) j(LEFT) k(DOWN) l(RIGHT)\n");
    printf("Eat more food will win the game\n");
    printf("Remain food:%d\n", numberOfFood - ScoreA - ScoreB);
}

void control() {
     switch (_getche()) {
        case UP:
            system("cls"); //清空
            dirPlayerA_Y = -1;
            dirPlayerA_X = 0;
            break;
        case DOWN:
            system("cls"); //清空
            dirPlayerA_Y = 1;
            dirPlayerA_X = 0;
            break;
        case LEFT:
            system("cls"); //清空
            dirPlayerA_Y = 0;
            dirPlayerA_X = -1;
            break;
        case RIGHT:
            system("cls"); //清空
            dirPlayerA_Y = 0;
            dirPlayerA_X = 1;
            break;
        case UP_:
            system("cls"); //清空
            dirPlayerB_Y = -1;
            dirPlayerB_X = 0;
            break;
        case DOWN_:
            system("cls"); //清空
            dirPlayerB_Y = 1;
            dirPlayerB_X = 0;
            break;
        case LEFT_:
            system("cls"); //清空
            dirPlayerB_Y = 0;
            dirPlayerB_X = -1;
            break;
        case RIGHT_:
            system("cls"); //清空
            dirPlayerB_Y = 0;
            dirPlayerB_X = 1;
            break;
        }
}

void processA() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (map[i][j] == 2) {
                //超出陣列範圍處理
                if ((i + dirPlayerA_Y < 0) && (i + dirPlayerA_Y) >= 15) {
                    continue;
                }
                if ((i + dirPlayerA_X < 0) && (i + dirPlayerA_X) >= 15) {
                    continue;
                }
                //下一步是路
                if (map[i + dirPlayerA_Y][j + dirPlayerA_X] == 1 && (dirPlayerA_X || dirPlayerA_Y)) {
                    map[i + dirPlayerA_Y][j + dirPlayerA_X] = 2;
                    map[i][j] = 1;
                    dirPlayerA_X = 0;
                    dirPlayerA_Y = 0;
                    stepA++;
                    return;
                }
                //下一步是食物
                else if (map[i + dirPlayerA_Y][j + dirPlayerA_X] == 4 && (dirPlayerA_X || dirPlayerA_Y)) {
                    map[i + dirPlayerA_Y][j + dirPlayerA_X] = 2;
                    map[i][j] = 1;
                    ScoreA++;
                    dirPlayerA_X = 0;
                    dirPlayerA_Y = 0;
                    stepA++;
                    return;
                }
                //下一步是道具
                else if (map[i + dirPlayerA_Y][j + dirPlayerA_X] == 5 && (dirPlayerA_X || dirPlayerA_Y)) {
                    map[i + dirPlayerA_Y][j + dirPlayerA_X] = 2;
                    map[i][j] = 1;
                    isPlayerBGhost = 1;
                    oriStepB = stepB;
                    dirPlayerA_X = 0;
                    dirPlayerA_Y = 0;
                    stepA++;
                    return;
                }
                //下一步是對手且對手是鬼
                else if (isPlayerBGhost && map[i + dirPlayerA_Y][j + dirPlayerA_X] == 3) {
                    map[14][13] = 3;
                    map[i + dirPlayerA_Y][j + dirPlayerA_X] = 2;
                    map[i][j] = 1;
                    stepA++;
                    //變回原本的
                    isPlayerBGhost = 0;
                    dirPlayerA_X = 0;
                    dirPlayerA_Y = 0;
                    return;
                }
                else if (map[i + dirPlayerA_Y][j + dirPlayerA_X] == 0) {
                    
                    return;
                }
            }
        }
    }
}

void processB() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (map[i][j] == 3) {
                //超出陣列範圍處理
                if ((i + dirPlayerB_Y < 0) && (i + dirPlayerB_Y) >= 15) {
                    continue;
                }
                if ((i + dirPlayerB_X < 0) && (i + dirPlayerB_X) >= 15) {
                    continue;
                }

                if (map[i + dirPlayerB_Y][j + dirPlayerB_X] == 1 && (dirPlayerB_X || dirPlayerB_Y)) {
                    map[i + dirPlayerB_Y][j + dirPlayerB_X] = 3;
                    map[i][j] = 1;
                    dirPlayerB_X = 0;
                    dirPlayerB_Y = 0;
                    stepB++;
                    return;
                }
                //下一步食物
                else if (map[i + dirPlayerB_Y][j + dirPlayerB_X] == 4 && (dirPlayerB_X || dirPlayerB_Y)) {
                    map[i + dirPlayerB_Y][j + dirPlayerB_X] = 3;
                    map[i][j] = 1;
                    ScoreB++;
                    dirPlayerB_X = 0;
                    dirPlayerB_Y = 0;
                    stepB++;
                    return;
                }
                //下一步是道具
                else if (map[i + dirPlayerB_Y][j + dirPlayerB_X] == 5 && (dirPlayerB_X || dirPlayerB_Y)) {
                    map[i + dirPlayerB_Y][j + dirPlayerB_X] = 3;
                    map[i][j] = 1;
                    isPlayerAGhost = 1;
                    oriStepA = stepA;
                    dirPlayerB_X = 0;
                    dirPlayerB_Y = 0;
                    stepB++;
                    return;
                }
                //下一步是對手且是鬼
                else if (isPlayerAGhost && map[i + dirPlayerB_Y][j + dirPlayerB_X] == 2) {
                    map[0][1] = 2;
                    map[i + dirPlayerB_Y][j + dirPlayerB_X] = 3;
                    map[i][j] = 1;
                    //變回原本的
                    isPlayerAGhost = 0;
                    dirPlayerB_X = 0;
                    dirPlayerB_Y = 0;
                    stepB++;
                    return;
                }
                else if (map[i + dirPlayerB_Y][j + dirPlayerB_X] == 0) {
                    return;
                }
            }
        }
    }
}

void generateFood() {
    for (int i = 1; i < 14; i++) {
        for (int j = 1; j < 14; j++) {
            if (map[i][j] == 1) {
                route.push_back(i * 100 + j);
            }
        }
    }
    int route_length = route.size();
    //printf("%d\n", route_length);
    //產生隨機地點食物
    //先跑完整個map將有路的座標記錄在vector裡面
    //隨機產生一個數字小於等於vector大小
    //取得vector中隨機的點
    for(int idx = 0;idx<numberOfFood;idx++) {
        while (1) {
            //防止兩個食物出現在同一點
            int foodLoc = rand() % route_length;
            int foodY = route.at(foodLoc) / 100;
            int foodX = route.at(foodLoc) % 100;
            if (map[foodY][foodX] == 4) continue;
            else {
                map[foodY][foodX] = 4;
                break;
            }
        }
    }
}

void overDisplay() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (map[i][j] == 0)
                printf("█");
            else if (map[i][j] == 1)
                printf("　");
            else if (map[i][j] == 2 && !isPlayerAGhost) //PlayerA
                printf("Ｘ");
            else if (map[i][j] == 2 && isPlayerAGhost) //PlayerA
                printf("x ");
            else if (map[i][j] == 3 && !isPlayerBGhost) //PlayerB
                printf("Ｏ");
            else if (map[i][j] == 3 && isPlayerBGhost) //PlayerB
                printf("o ");
            else if (map[i][j] == 4)
                printf("＊");
            else if (map[i][j] == 5)
                printf("＃");
        }
        printf("\n");
    }
    printf("A Score:%d\tStep:%d\n", ScoreA, stepA);
    printf("B Scord:%d\tStep:%d\n", ScoreB, stepB);
    printf("Remain food:%d\n\n", numberOfFood - ScoreA - ScoreB);
    if (ScoreA > ScoreB)
        printf("PlayerA Won!\n\n");
    else
        printf("PlayerB Won!\n\n");
    

}

void saveGameStatus() {
    list tmp;
    printf("請輸入你的名字:");
    scanf("%s", tmp.nme);
    ScoreA > ScoreB ? tmp.highScore = ScoreA : tmp.highScore = ScoreB;
    fprintf(history, "%s %d\n", tmp.nme, tmp.highScore);
    printf("%s %d 已記錄\n", tmp.nme, tmp.highScore);
    fclose(history);
}

void resetStatus() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            map[i][j] = ori_map[i][j];
        }
    }
    dirPlayerA_X = 0;
    dirPlayerA_Y = 0;
    dirPlayerB_X = 0;
    dirPlayerB_Y = 0;
    ScoreA = 0;
    ScoreB = 0;
    //vector清空可有可無 因為地圖固定
    route.clear();
    isPlayerAGhost = 0;
    isPlayerBGhost = 0;
    oriStepA = 0;
    oriStepB = 0;
    stepA = 0;
    stepB = 0;
    generateFood();
}

int GameOver() {
    if (ScoreA + ScoreB == numberOfFood) return 1;
    else return 0;
}


