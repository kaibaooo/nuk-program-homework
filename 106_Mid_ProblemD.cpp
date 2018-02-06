#include<stdio.h>
#include<stdlib.h>

int main(){
	int count = 1;
	int arr[5000] = {0};
	arr[0] = 2;
	for(int i=3;i<=5000;i++){
		for(int j=2;j<=i-1;j++){
			if(i-1==j){
				arr[count] = i;
				count++;
			}
			if(i%j==0){
				break;
			}
			else 
				continue;
		}
	}
	/*
	for(int i = 0;i<count;i++){
		printf("%d ", arr[i]);
	}
	printf("\n\n\n");
	*/
	int k;
	scanf("%d", &k);
	for(int i = 0;i<arr[i];i++){
		if(k%arr[i]==0 ){
			printf("%d ", arr[i]);
		}
	}
	printf("\n");
	system("pause");
	return 0;
}