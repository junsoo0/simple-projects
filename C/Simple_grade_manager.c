#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct student
{
	char name[20];
	int id;
	int score;
} student;

void output(student*, int);
double avg(student*, int);
double std(student*, int);

int main()
{
	int menu;
	int i;
	int n;

	printf(">>> �޴� <<<\n");
	printf("1. ������ �Է�\n");
	printf("2. ������ ���\n");
	printf("3. �������\n");
	printf("4. ǥ������\n");
	printf("5. ����\n");
	printf("------------------------------\n");

	printf("�޴��� �����Ͻÿ�: ");
	do
	{
		scanf("%d", &menu);
	} while (!(menu == 1 || menu == 2 || menu == 3 || menu == 4 || menu == 5));

	student* input = { NULL };


	while (menu != 5)
	{
		if (menu == 1)
		{
			printf("�迭�� ũ�⸦ �Է��Ͻÿ�: ");
			do
			{
				scanf("%d", &n);
			} while (n <= 0);

			input = (student*)malloc(sizeof(student) * n);

			for (i = 0; i < n; i++)
			{
				printf("data %d>\n", i + 1);

				printf("�̸�: ");
				scanf("%s", input[i].name);

				printf("�й�: ");
				scanf("%d", &input[i].id);

				printf("����: ");
				scanf("%d", &input[i].score);

				getchar();
			}
		}
		else if (menu == 2)
			output(input, n);
		else if (menu == 3)
			printf("�������: %f\n", avg(input, n));
		else
			printf("ǥ������: %f\n", std(input, n));

		printf("�޴��� �����Ͻÿ�: ");
		scanf("%d", &menu);
	}


	return 0;
}

void output(student* input, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		printf("�̸�: %s\n", input[i].name);
		printf("�й�: %d\n", input[i].id);
		printf("����: %d\n", input[i].score);
	}
}

double avg(student* input, int n)
{
	int i;
	double sum;

	sum = 0.0;
	for (i = 0; i < n; i++)
	{
		sum += (double)input[i].score;
	}

	return sum / (double)n;
}

double std(student* input, int n)
{
	int i;
	double sum;

	sum = 0.0;
	for (i = 0; i < n; i++)
	{
		sum += pow((input[i].score - avg(input, n)), 2);
	}

	return sqrt(sum / (double)n);
}