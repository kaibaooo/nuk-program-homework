//Problem:
/*
前使用的格里曆閏年規則如下：
1.西元年分除以 400 可整除，為閏年。
2.西元年分除以 4 可整除但除以 100 不可整除，為閏年。
3.西元年分除以 4 不可整除，為平年。
4.西元年分除以 100 可整除但除以 400 不可整除，為平年
請設計一個程式，輸入一個年份，輸出是否為閏年。
*/
#include <stdio.h>
#include <stdlib.h>

int main(){
    int year;
	    while(scanf("%d",&year) != EOF){
			if(year % 400 == 0){
			    printf("閏年\n");
			}
			else if((year % 4 == 0) && (year % 100 != 0)){
			    printf("閏年\n");
			}
			else{
			    printf("不是閏年\n");
			}
		}
	system("pause");
    return 0;
}
