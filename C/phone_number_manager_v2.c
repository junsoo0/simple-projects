#include <stdio.h>
#include <string.h>
#define LEN 20

typedef struct {
	char name[LEN];
	char tel[LEN];
} info;

int file_read(info*, int*);
void print_menu(int*);
void ins(info*, int*);
void del(info*, int*);
void ser(info*, int);
void print_all(info*, int);
int file_write(info*, int);

int main() {
	int n = 0, i = 0;
	info group[100];
	int stat;

	stat = file_read(group, &i);

	if (stat == 2) {
		printf("file read error!\n");

		return 1;
	}
	else if (stat == 3) {
		printf("file close error!\n");

		return 1;
	}

	while (1) {
		print_menu(&n);
		switch (n) {
		case 1:
			ins(group, &i);
			break;
		case 2:
			del(group, &i);
			break;
		case 3:
			ser(group, i);
			break;
		case 4:
			print_all(group, i);
			break;
		case 5:
			stat = file_write(group, i);

			if (stat == 1) {
				printf("file open error!\n");

				return 1;
			}
			else if (stat == 2) {
				printf("file read error!\n");

				return 1;
			}
			else if (stat == 3) {
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

int file_read(info* ifp, int* ip) {
	FILE* fp;
	int opstat;
	
	opstat = fopen_s(&fp, "number_management.txt", "rt");
	if (opstat == 0) {
		while (fscanf_s(fp, "%s %s", ifp[*ip].name, LEN, ifp[*ip].tel, LEN) != EOF)
			(* ip)++;
		if (feof(fp) == 0)
			return 2;

		if (fclose(fp) != 0)
			return 3;
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

void ins(info* ifp, int* ip) {
	printf("Input Name: ");
	scanf_s("%s", ifp[*ip].name, LEN);
	printf("Input Tel Number: ");
	scanf_s("%s", ifp[*ip].tel, LEN);

	(*ip)++;

	printf("Data Inserted\n");
	puts("");
}

void del(info* ifp, int* ip) {
	char input_name[LEN];
	int j, k;

	printf("Input Name: ");
	scanf_s("%s", input_name, LEN);

	for (j = 0; j < *ip; j++) {
		if (strcmp(input_name, ifp[j].name) == 0) {
			for (k = j; k < *ip - 1; k++) {
				ifp[k] = ifp[k + 1];
			}
			(*ip)--;
			printf("Data Deleted\n");
			break;
		}
		if (j == *ip - 1)
			printf("no exist\n");
	}

	puts("");
}

void ser(info* ifp, int i) {
	char input_name[LEN];
	int j;

	printf("Input Name: ");
	scanf_s("%s", input_name, LEN);

	for (j = 0; j < i; j++) {
		if (strcmp(input_name, ifp[j].name) == 0) {
			printf("Name: %-10s", ifp[j].name);
			printf("Tel: %s\n", ifp[j].tel);
			break;
		}
		if (j == i - 1) {
			printf("no exist\n");
		}
	}
	puts("");
}

void print_all(info* ifp, int i) {
	int j;
	
	for (j = 0; j < i; j++) {
		printf("Name: %-10s", ifp[j].name);
		printf("Tel: %s\n", ifp[j].tel);
	}
	puts("");
}

int file_write(info* ifp, int i) {
	FILE* fp;
	int opstat;
	int j;
	
	opstat = fopen_s(&fp, "number_management.txt", "wt");
	if (opstat != 0)
		return 1;

	for (j = 0; j < i; j++) {
		fprintf(fp, "%s %s\n", ifp[j].name, ifp[j].tel);
	}

	if (fclose(fp) != 0)
		return 3;

	return 0;
}