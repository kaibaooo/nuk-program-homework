/*
//輸入十位數字 排大小
//限定將交換以及泡泡排序寫成獨立Function
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubbleSort(int data[]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (data[j] > data[j + 1]) {
                swap(&data[j], &data[j + 1]);
            }
        }
    }
}

int main() {
    int nums[10];
    for (int i = 0; i < 10; i++) {
        scanf("%d", &nums[i]);
    }
    bubbleSort(nums);
    for (int i = 0; i < 10; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    system("pause");
    return 0;
}