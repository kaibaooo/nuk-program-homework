//Problem:
/*
請將兩個變數進行四則運算(加減乘除)後的結果分別以整數、浮點數的形式輸出
*/

#include<stdio.h>
#include<stdlib.h>

int main(){
	int a = 3;
	float b = 5.5;
	printf("%d %d %d %d\n", (float)a+b,a-b,a*b,a/b);
	printf("%f %f %f %f\n", (float)(a+b),a-b,a*b,a/b);
	system("pause");
	return 0;
}

