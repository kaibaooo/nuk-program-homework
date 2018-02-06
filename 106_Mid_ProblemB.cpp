#include<stdio.h>
#include<stdlib.h>

int UVA100(int);

int main(){
	int n = 0;
	scanf("%d", &n);
	printf("%d ", n);
	UVA100(n);
	/*
	while(n!=1){
		if(n%2==1){
			n = 3 * n + 1;
		}
		else{
			n = n / 2;
		}
		printf("%d ", n);
	}
	*/
	system("pause");
	return 0;
}

int UVA100(int n_){
	if(n_==1) return 0;
	if(n_%2==1){
		printf("%d ", 3 * n_ + 1);
		return UVA100(3 * n_ + 1);
	}
	if(n_%2==0){
		printf("%d ", n_ / 2);
		return UVA100(n_ / 2);
	}

	return 0;
}