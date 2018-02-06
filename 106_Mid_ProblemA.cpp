#include<stdio.h>
#include<stdlib.h>

int main(){
	int n;
	float sum = 0;
	scanf("%d", &n);
	for(int i = 1;i<=n;i++){
		sum += (float)1/(i*i);
	}
	printf("%f\n", sum);
	system("pause");
	return 0;
}