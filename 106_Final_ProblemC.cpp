/*
//檔案IO
//格式id cost nam date
//包含顯示資料/刪除特定資料(不顯示)/修改或新增資料
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

struct book{
    int id;
    int cost;
    char name[20];
    char date[20];
};

void showMenu() {
    printf("1.印出存在的資料\n");
    printf("2.刪除某筆資料\n");
    printf("3.修改/新增資料\n");
	printf("4.清空畫面\n");
}

int main() {
    int count = 0;
    book info;
	
    FILE *fptr = fopen("book.dat", "wb");
	printf("輸入多筆資料(編號 價格 書名 出版日):\n");
    while (scanf("%d %d %s %s", &info.id, &info.cost, info.name, info.date) != EOF) {
        fwrite(&info, sizeof(book), 1, fptr);
        count++;
    }
    fclose(fptr);
    while (1) {
        showMenu();
        int choice = 0;
		printf("要幹嘛:\n");
		
        scanf("%d", &choice);
        if (choice == 1) {
            fptr = fopen("book.dat", "rb");
            while (1) {
                fread(&info, sizeof(book), 1, fptr);
                if (feof(fptr) != 0) break;
                if(info.id != -1)
                    printf("%d %d %s %s\n", info.id, info.cost, info.name, info.date);
            }
            fclose(fptr);
        }
        else if (choice == 2) {
            int del_id = 0;
            int offset = 0;
            book del = { -1,-1, "","" };
			printf("輸入要刪除的資料編號\n");
            scanf("%d", &del_id);
            fptr = fopen("book.dat", "rb+");
            while (1) {
                fread(&info, sizeof(book), 1, fptr);
                if (feof(fptr) != 0) break;
                if (info.id == del_id) {
                    //info = {-1, -1, "",""};
                    fseek(fptr, sizeof(book) * offset, SEEK_SET);
                    fwrite(&del, sizeof(book), 1, fptr);
                    break;
                }
                offset++;
            }
            fclose(fptr);
        }
        else if (choice == 3) {
            int new_id = 0;
            int offset = 0;
            book newData;
			printf("請輸入欲更新之編號\n");
            scanf("%d", &new_id);
            printf("請輸入更新後的資料:\n");
            scanf("%d %d %s %s", &newData.id, &newData.cost, newData.name, newData.date);
            fptr = fopen("book.dat", "rb+");
            while (1) {
                fread(&info, sizeof(book), 1, fptr);
                if (feof(fptr) != 0) {
                    fseek(fptr, 0, SEEK_END);

                    fwrite(&newData, sizeof(book), 1, fptr);
					printf("查無此編號，已將資料加入\n");
                    break;
                }
                if (info.id == new_id) {
                    fseek(fptr, sizeof(book) * offset, SEEK_SET);
                    fwrite(&newData, sizeof(book), 1, fptr);
                    break;
                }
                offset++;
            }
            fclose(fptr);
            offset = 0;
        }
		else{
			system("cls");
			continue;
		}
        
    }
    
    system("pause");
    return 0;
}