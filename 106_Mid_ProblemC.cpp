#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
	srand(time(NULL));
	int N = 0;
	scanf("%d", &N);
	int *nums = (int*)malloc(sizeof(int) * N);
	for(int i = 0;i<N;i++){
		nums[i] = rand() % 51 + 50;
	}
	//sort
	for(int i = 0;i<N-1;i++){
		for(int j = 0;j<N-1;j++){
			if(nums[j]>=nums[j+1]){
				int temp = nums[j];
				nums[j] = nums[j+1];
				nums[j+1] = temp;
			}
		}
	}
	for(int i = 0;i<N;i++){
		printf("%d ", nums[i]);
	}
	printf("\n");
	int k = 0;
	scanf("%d", &k);
	bool flag = false;
	int min = 0, max = N;
	while(1){
		
		int mid = (max+min)/2;
		if(k==nums[mid]){
			printf("%d\n", mid);
			break;
		}
		if(k > nums[mid]){
			min = mid;
		}
		else{
			max = mid;
		}
		if(max-min==1 && nums[mid-1]!=k) {
			printf("¤£¦s¦b\n");
			break;
		}
		else if(max-min==1 && nums[mid-1]==k){
			printf("%d ",min);
			break;
		}
	}
	system("pause");
	return 0;
}