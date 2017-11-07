//Problem:
/*
請設計一個程式，印出 1~5 排列組合而成，互不相同且無重複數字的所有 3
位數字，數字間請用空白隔開。
*/

#include<stdio.h>
#include<stdlib.h>

int main(){
	int a = 1, b=1,c=1;

	while(a<=5){
		while(b<=5){
			if(a == b) {
				b++;
				continue;
			}
			while(c<=5){
				if(b == c || a ==c) {
					c++;
					continue;
				}
				else{
				printf("%d%d%d ", a, b, c);
				c++;
				}
			}
			b++;
		}
		a++;
	}
	system("pause");
	return 0;
}