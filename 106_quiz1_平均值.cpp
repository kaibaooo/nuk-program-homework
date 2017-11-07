//Problem:
/*
設計一個程式，讓使用者輸入隨意的值，直到輸入 9999 時結束，算出輸入
的值的平均值(不包含 9999)，印到小數點後兩位。
*/

#include<stdio.h>
#include<stdlib.h>

int main(){
	int n = 0,count = 0;
	float sum = 0;
	printf("Enter an Integer ( 9999 to end ): ");
	while(scanf("%d", &n) != EOF){
		if(n==9999) 
			break;
		sum += n;
		count++;
		printf("Enter an Integer ( 9999 to end ): ");
	}
	if(count)
		printf("The average is: %.2f\n", sum / count);
	else
		printf("The average is: 0\n");
	system("pause");
	return 0;
}