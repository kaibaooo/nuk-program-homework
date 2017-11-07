//Problem:
/*
組合數目計算
C(n,k)表示 n 個物件中取 k 個的組合數目
而數學上有 C(n,k) = C(n-1,k-1) + C(n-1,k)之性質
利用此性質設計一遞迴函式解 C(n,k)
讓使用者輸入兩個正整數分別代表 n 與 k，利用上述函式輸出
C(n,k)之結果
注意：本題禁止使用遞迴函式以外的方法解題
*/


#include<stdlib.h>
#include<stdio.h>

unsigned long long int power(int);

int main(){
	int n = 0, k = 0;
	while(1){
		printf("n = ");
		scanf("%u", &n);
		printf("k = ");
		scanf("%u", &k);
		if(n<=0 || k<=0 || n<k){
			printf("error\n");
			continue;
		}
		if(n==1 && k == 1){
			printf("%d\n", 1);
			continue;
		}
		unsigned long long int data1 = power(n-1);
		unsigned long long int data2 = power(k-1);
		unsigned long long int data3 = power(k);
		unsigned long long int data4 = power(n-k);
		unsigned long long int data5 = power(n-1-k);
		unsigned long long int ans = (data1/(data2*data4) + data1/(data3*data5));
		printf("%llu\n", ans);
	}
	system("pause");
	return 0;
}

unsigned long long int power(int r){
	if(r>1)
		return r * power(r-1);
	else
		return 1;
}

//n-1-(k-1) = n-1-k+1 = n-k
//data1/(double)(data2*data4) + data1/(double)(data3*data5);