//Problem:
/*
親戚計算機
 每次過年都要回家跟長輩寒暄一下，但是都不知道這個要叫叔叔
還是舅舅？這個是堂哥還是堂姊？阿姨的兒子又要叫什麼?姑姑又是
我的誰？唉唷煩死了，高中公民沒學好的助教請你們幫他設計一個簡
易版的親戚計算機，讓他可以快速喊出正確的稱呼。
簡易版的計算機紀錄了以下的資訊:
1.爸爸 的 哥哥/弟弟/姊姊/妹妹 稱呼
2.媽媽 的 哥哥/弟弟/姊姊/妹妹 稱呼
3.爸爸 的 哥哥/弟弟/姊姊/妹妹 的 兒子/女兒 稱呼(比較年長的)
4.媽媽 的 哥哥/弟弟/姊姊/妹妹 的 兒子/女兒 稱呼(比較年長的)
*/


#include<stdio.h>
#include<stdlib.h>

int main(){
	int a = 0, b = 0, c = 0;
	printf("==========================\n");
	printf("|       親戚計算機       |\n");
	printf("==========================\n");
	printf("請輸入操作: 1.爸爸 2.媽媽\n");
	scanf("%d", &a);
	if(a==1){
		//爸爸
		printf("爸爸 的 1.哥哥 2.弟弟 3.姊姊 4.妹妹\n");
		scanf("%d", &b);
		switch(b){
		case 1:    //哥哥
			printf("爸爸 的 哥哥 的 1.兒子 2.女兒 3.我就是要查爸爸的哥哥\n");
			scanf("%d", &c);
			switch(c){
			case 1:    //兒子
				printf("爸爸 的 哥哥 的 兒子 是: 堂哥\n");
				break;
			case 2:    //女兒
				printf("爸爸 的 哥哥 的 女兒 是: 堂姐\n");
				break;
			case 3:    //爸爸的哥哥
				printf("爸爸 的 哥哥 是: 伯父\n");
				break;
			}
			break;
		case 2:    //弟弟
			printf("爸爸 的 弟弟 的 1.兒子 2.女兒 3.我就是要查爸爸的弟弟\n");
			scanf("%d", &c);
			switch(c){
			case 1:
				printf("爸爸 的 弟弟 的 兒子 是: 堂哥\n");
				break;
			case 2:

				printf("爸爸 的 弟弟 的 女兒 是: 堂姊\n");
				break;
			case 3:

				printf("爸爸 的 弟弟 是: 叔叔\n");
				break;
			}
			break;
		case 3:    //姐姐
			printf("爸爸 的 姐姐 的 1.兒子 2.女兒 3.我就是要查爸爸的姐姐\n");
			scanf("%d", &c);
			switch(c){
			case 1:
				printf("爸爸 的 姐姐 的 兒子 是: 表哥\n");
				break;
			case 2:

				printf("爸爸 的 姐姐 的 女兒 是: 表姐\n");
				break;
			case 3:

				printf("爸爸 的 姐姐 是: 姑媽\n");
				break;
			}
			break;
		case 4:    //妹妹
			printf("爸爸 的 妹妹 的 1.兒子 2.女兒 3.我就是要查爸爸的妹妹\n");
			scanf("%d", &c);
			switch(c){
			case 1:
				printf("爸爸 的 妹妹 的 兒子 是: 表哥\n");
				break;
			case 2:
				printf("爸爸 的 妹妹 的 女兒 是: 表姐\n");
				break;
			case 3:
				printf("爸爸 的 妹妹 是: 姨媽\n");
				break;
			}
			break;
		}
	}
	else{    //媽媽
		printf("媽媽 的 1.哥哥 2.弟弟 3.姊姊 4.妹妹\n");
		scanf("%d", &b);
		switch(b){
		case 1:    //哥哥
			printf("媽媽 的 哥哥 的 1.兒子 2.女兒 3.我就是要查媽媽的哥哥\n");
			scanf("%d", &c);
			switch(c){
			case 1:
				printf("媽媽 的 哥哥 的 兒子 是: 表哥\n");
				break;
			case 2:
				printf("媽媽 的 哥哥 的 女兒 是: 表姐\n");
				break;
			case 3:
				printf("媽媽 的 哥哥 是: 舅舅\n");
				break;
			}
			break;
		case 2:    //弟弟
			printf("媽媽 的 弟弟 的 1.兒子 2.女兒 3.我就是要查媽媽的弟弟\n");
			scanf("%d", &c);
			switch(c){
			case 1:
				printf("媽媽 的 弟弟 的 女兒 是: 表哥\n");
				break;
			case 2:
				printf("媽媽 的 弟弟 的 女兒 是: 表姐\n");
				break;
			case 3:
				printf("媽媽 的 哥哥 是: 舅舅\n");
				break;
			}
			break;
		case 3:    //姐姐
			printf("媽媽 的 姐姐 的 1.兒子 2.女兒 3.我就是要查媽媽的姐姐\n");
			scanf("%d", &c);
			switch(c){
			case 1:
				printf("媽媽 的 姐姐 的 兒子 是: 表哥\n");
				break;
			case 2:
				printf("媽媽 的 姐姐 的 女兒 是: 表姐\n");
				break;
			case 3:
				printf("媽媽 的 姐姐 是: 姨媽\n");
				break;
			}
			break;
		case 4:    //妹妹
			printf("媽媽 的 妹妹 的 1.兒子 2.女兒 3.我就是要查媽媽的妹妹\n");
			scanf("%d", &c);
			switch(c){
			case 1:
				printf("媽媽 的 妹妹 的 兒子 是: 表哥\n");
				break;
			case 2:
				printf("媽媽 的 妹妹 的 女兒 是: 表姐\n");
				break;
			case 3:
				printf("媽媽 的 妹妹 是: 姨媽\n");
				break;
			}
			break;
		}
	}

	system("pause");
	return 0;
}