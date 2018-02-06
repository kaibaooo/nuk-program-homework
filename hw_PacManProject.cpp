/*
//PlayerA WASD ���W��
//PlayerB IJKL �k�U��
//�������D��(#)�i�H�����ܤp �I����ɥi�H�����L ���L�^���I
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
//A,B���a���ʤ�V
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
    printMap(); //�L�a��
    while (1) {
        //printMap(); //�L�a��
        if (_kbhit()) {
            system("cls");
            control(); //���a����L
            processA(); //���ʰ}�C�����aA����m
            processB(); //���ʰ}�C�����aB����m
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
            printf("1. �A�Ӱ�\n2. ��ڨ�\n");
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
                printf("�i");
            else if (map[i][j] == 1)
                printf("�@");
            else if (map[i][j] == 2 && !isPlayerAGhost) //PlayerA
                printf("��");
            else if (map[i][j] == 2 && isPlayerAGhost) //PlayerA
                printf("x ");
            else if (map[i][j] == 3 && !isPlayerBGhost) //PlayerB
                printf("��");
            else if (map[i][j] == 3 && isPlayerBGhost) //PlayerB
                printf("o ");
            else if (map[i][j] == 4)
                printf("��");
            else if (map[i][j] == 5)
                printf("��");
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
            system("cls"); //�M��
            dirPlayerA_Y = -1;
            dirPlayerA_X = 0;
            break;
        case DOWN:
            system("cls"); //�M��
            dirPlayerA_Y = 1;
            dirPlayerA_X = 0;
            break;
        case LEFT:
            system("cls"); //�M��
            dirPlayerA_Y = 0;
            dirPlayerA_X = -1;
            break;
        case RIGHT:
            system("cls"); //�M��
            dirPlayerA_Y = 0;
            dirPlayerA_X = 1;
            break;
        case UP_:
            system("cls"); //�M��
            dirPlayerB_Y = -1;
            dirPlayerB_X = 0;
            break;
        case DOWN_:
            system("cls"); //�M��
            dirPlayerB_Y = 1;
            dirPlayerB_X = 0;
            break;
        case LEFT_:
            system("cls"); //�M��
            dirPlayerB_Y = 0;
            dirPlayerB_X = -1;
            break;
        case RIGHT_:
            system("cls"); //�M��
            dirPlayerB_Y = 0;
            dirPlayerB_X = 1;
            break;
        }
}

void processA() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (map[i][j] == 2) {
                //�W�X�}�C�d��B�z
                if ((i + dirPlayerA_Y < 0) && (i + dirPlayerA_Y) >= 15) {
                    continue;
                }
                if ((i + dirPlayerA_X < 0) && (i + dirPlayerA_X) >= 15) {
                    continue;
                }
                //�U�@�B�O��
                if (map[i + dirPlayerA_Y][j + dirPlayerA_X] == 1 && (dirPlayerA_X || dirPlayerA_Y)) {
                    map[i + dirPlayerA_Y][j + dirPlayerA_X] = 2;
                    map[i][j] = 1;
                    dirPlayerA_X = 0;
                    dirPlayerA_Y = 0;
                    stepA++;
                    return;
                }
                //�U�@�B�O����
                else if (map[i + dirPlayerA_Y][j + dirPlayerA_X] == 4 && (dirPlayerA_X || dirPlayerA_Y)) {
                    map[i + dirPlayerA_Y][j + dirPlayerA_X] = 2;
                    map[i][j] = 1;
                    ScoreA++;
                    dirPlayerA_X = 0;
                    dirPlayerA_Y = 0;
                    stepA++;
                    return;
                }
                //�U�@�B�O�D��
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
                //�U�@�B�O���B���O��
                else if (isPlayerBGhost && map[i + dirPlayerA_Y][j + dirPlayerA_X] == 3) {
                    map[14][13] = 3;
                    map[i + dirPlayerA_Y][j + dirPlayerA_X] = 2;
                    map[i][j] = 1;
                    stepA++;
                    //�ܦ^�쥻��
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
                //�W�X�}�C�d��B�z
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
                //�U�@�B����
                else if (map[i + dirPlayerB_Y][j + dirPlayerB_X] == 4 && (dirPlayerB_X || dirPlayerB_Y)) {
                    map[i + dirPlayerB_Y][j + dirPlayerB_X] = 3;
                    map[i][j] = 1;
                    ScoreB++;
                    dirPlayerB_X = 0;
                    dirPlayerB_Y = 0;
                    stepB++;
                    return;
                }
                //�U�@�B�O�D��
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
                //�U�@�B�O���B�O��
                else if (isPlayerAGhost && map[i + dirPlayerB_Y][j + dirPlayerB_X] == 2) {
                    map[0][1] = 2;
                    map[i + dirPlayerB_Y][j + dirPlayerB_X] = 3;
                    map[i][j] = 1;
                    //�ܦ^�쥻��
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
    //�����H���a�I����
    //���]�����map�N�������y�аO���bvector�̭�
    //�H�����ͤ@�ӼƦr�p�󵥩�vector�j�p
    //���ovector���H�����I
    for(int idx = 0;idx<numberOfFood;idx++) {
        while (1) {
            //�����ӭ����X�{�b�P�@�I
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
                printf("�i");
            else if (map[i][j] == 1)
                printf("�@");
            else if (map[i][j] == 2 && !isPlayerAGhost) //PlayerA
                printf("��");
            else if (map[i][j] == 2 && isPlayerAGhost) //PlayerA
                printf("x ");
            else if (map[i][j] == 3 && !isPlayerBGhost) //PlayerB
                printf("��");
            else if (map[i][j] == 3 && isPlayerBGhost) //PlayerB
                printf("o ");
            else if (map[i][j] == 4)
                printf("��");
            else if (map[i][j] == 5)
                printf("��");
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
    printf("�п�J�A���W�r:");
    scanf("%s", tmp.nme);
    ScoreA > ScoreB ? tmp.highScore = ScoreA : tmp.highScore = ScoreB;
    fprintf(history, "%s %d\n", tmp.nme, tmp.highScore);
    printf("%s %d �w�O��\n", tmp.nme, tmp.highScore);
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
    //vector�M�ťi���i�L �]���a�ϩT�w
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


