//Problem:
/*
寫一個矩形，起始座標為(0,0)，先輸入矩形長寬。
再輸入一個點的座標，再判斷點是否在矩形內(再邊上也算)，在就輸出
inside，不在就輸出 outside。
*/

#include<stdio.h>
#include<stdlib.h>

int main(){
	int a = 0, b = 0;
	int c = 0, d = 0;
	printf("輸入矩形長寬 : ");
	scanf("%d %d", &a, &b);
	printf("矩形長%d 寬%d\n",a , b);
	printf("輸入座標 判斷該點是inside或是outside: ");
	scanf("%d %d", &c, &d);
	
	if(c<=a && d<=b){
		printf("inside\n");
	}
	else{
		printf("outside\n");
	}
	system("pause");
	return 0;
}