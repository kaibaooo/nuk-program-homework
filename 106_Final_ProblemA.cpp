/*
//分割電話號碼
//EX. 09-123456789  --> 
//09
//123456789
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
int main() {

    char input[11];
    scanf("%s", input);
    char *tmp;
    tmp = strtok(input, "-");
    while (tmp != NULL) {
        printf("%s\n", tmp);
        tmp = strtok(NULL, "-");
    }

    system("pause");
    return 0;
}