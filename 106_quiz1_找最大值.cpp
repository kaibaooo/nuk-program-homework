//Problem:
/*
請設計一個程式，輸入 4 個正整數後會印出 4 個數字中的最大值
*/

#include<stdio.h>
#include<stdlib.h>

int main(){
	int a = 0, b = 0, c = 0, d = 0;
	scanf("%d %d %d %d",&a, &b, &c, &d);
	if(a>=b && a>=c && a>=d) printf("max is %d\n", a);
	else if(b>=a && b>=c && b>=d) printf("max is %d\n", b);
	else if(c>=a && c>=b && c>=d) printf("max is %d\n", c);
	else printf("max is %d\n", d);
	system("pause");
	return 0;
}