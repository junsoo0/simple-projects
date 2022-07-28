#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 20

typedef struct {
	char name[LEN];
	char tel[LEN];
} info;

void print_menu(int*);

int main() {
	int n = 0, i = 0, j, k, s = 20;
	info* group;
	char input_name[LEN];
	FILE* fp;
	int opstat;
	
	group = (info*)malloc(sizeof(info) * 20);

	opstat = fopen_s(&fp, "number_management.txt", "rt");
	if (opstat == 0) {
		while (fscanf_s(fp, "%s %s", group[i].name, LEN, group[i].tel, LEN) != EOF) {
			i++;
			if (i == s) {
				s = s + 5;
				group = (info*)realloc(group, sizeof(info) * s);
			}
		}

		if (fclose(fp) != 0) {
			printf("file close error!\n");

			return 1;
		}
	}

	while (1) {
		print_menu(&n);
		switch (n) {
		case 1:
			printf("Input Name: ");
			scanf_s("%s", group[i].name, LEN);
			printf("Input Tel Number: ");
			scanf_s("%s", group[i].tel, LEN);

			i++;
			if (i == s) {
				s = s + 5;
				group = (info*)realloc(group, sizeof(info) * s);
			}

			printf("Data Inserted\n");
			puts("");
			break;
		case 2:
			printf("Input Name: ");
			scanf_s("%s", input_name, LEN);

			for (j = 0; j < i; j++) {
				if (strcmp(input_name, group[j].name) == 0) {
					for (k = j; k < i - 1; k++) {
						group[k] = group[k + 1];
					}
					i--;
					printf("Data Deleted\n");
					break;
				}
				if (j == i - 1)
					printf("no exist\n");
			}

			puts("");
			break;
		case 3:
			printf("Input Name: ");
			scanf_s("%s", input_name, LEN);

			for (j = 0; j < i; j++) {
				if (strcmp(input_name, group[j].name) == 0) {
					printf("Name: %-10s", group[j].name);
					printf("Tel: %s\n", group[j].tel);
					break;
				}
				if (j == i - 1) {
					printf("no exist\n");
				}
			}
			puts("");
			break;
		case 4:
			for (j = 0; j < i; j++) {
				printf("Name: %-10s", group[j].name);
				printf("Tel: %s\n", group[j].tel);
			}
			puts("");
			break;
		case 5:
			opstat = fopen_s(&fp, "number_management.txt", "wt");
			if (opstat != 0) {
				printf("file open error!\n");

				return 1;
			}

			for (j = 0; j < i; j++) {
				fprintf(fp, "%s %s\n", group[j].name, group[j].tel);
			}

			if (fclose(fp) != 0) {
				printf("file close error!\n");

				return 1;
			}
			return 0;
		default:
			printf("error!\n");
			puts("");
			break;
		}
	}

	return 0;
}

void print_menu(int* ip) {
	printf("***** MENU *****\n");
	printf("1. Insert\n");
	printf("2. Delete\n");
	printf("3. Search\n");
	printf("4. Print All\n");
	printf("5. Exit\n");
	printf("Choose the item: ");
	scanf_s("%d", ip);
}