/*
//�ɮ�IO
//�榡id cost nam date
//�]�t��ܸ��/�R���S�w���(�����)/�ק�ηs�W���
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
    printf("1.�L�X�s�b�����\n");
    printf("2.�R���Y�����\n");
    printf("3.�ק�/�s�W���\n");
	printf("4.�M�ŵe��\n");
}

int main() {
    int count = 0;
    book info;
	
    FILE *fptr = fopen("book.dat", "wb");
	printf("��J�h�����(�s�� ���� �ѦW �X����):\n");
    while (scanf("%d %d %s %s", &info.id, &info.cost, info.name, info.date) != EOF) {
        fwrite(&info, sizeof(book), 1, fptr);
        count++;
    }
    fclose(fptr);
    while (1) {
        showMenu();
        int choice = 0;
		printf("�n�F��:\n");
		
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
			printf("��J�n�R������ƽs��\n");
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
			printf("�п�J����s���s��\n");
            scanf("%d", &new_id);
            printf("�п�J��s�᪺���:\n");
            scanf("%d %d %s %s", &newData.id, &newData.cost, newData.name, newData.date);
            fptr = fopen("book.dat", "rb+");
            while (1) {
                fread(&info, sizeof(book), 1, fptr);
                if (feof(fptr) != 0) {
                    fseek(fptr, 0, SEEK_END);

                    fwrite(&newData, sizeof(book), 1, fptr);
					printf("�d�L���s���A�w�N��ƥ[�J\n");
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