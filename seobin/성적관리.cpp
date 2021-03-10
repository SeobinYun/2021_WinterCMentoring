//����
//1. ���� ����
//2. ����
//3. �����Է¿��� Grade ���� ������Ʈ �� �й� �������� ���� �����ϴ°�
//4. ���Ḯ��Ʈ �ƴ��� Ȯ��
//5. ���� ���

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
typedef struct student {
	char name[20]; //�л��̸�
	int ID; //�й�
	char password[30]; //��й�ȣ

	int total_credit; //�� �̼�����
	double total_GPA; //�� ����
	double average; // �������
	int rank; //��ü����
	struct student* next;
}Student;

typedef struct grade {
	int ID; //�й�
	char classname[20]; //�����̸�
	int grade; //����
	int credit; //�̼�����
	char GPA[3]; //���� ex) A+
	struct grade* next;
}Grade;

Student* stu_head, * stu_tail;
Grade* grd_head, * grd_tail;

char masterkey[30] = "123qwe";

void connect(Student* newNode);
void registerInfo(void);

int main(void) {
	int res = 0;
	FILE* ifp_s;
	FILE* ifp_g;
	ifp_s = fopen("student.txt", "w+");
	ifp_g = fopen("grade.txt", "w+");

	stu_head = NULL;
	stu_tail = NULL;
	grd_head = NULL;
	grd_tail = NULL;

	while (1) {
		printf("[ Menu ]\n1. ����Ȯ��\t2. �����Է�\t3. �л��������\t4. �л���������\t0. ���α׷� ����\n");
		scanf("%d", &res);
		switch (res) {
		case1:gradecheck(); //1. ����Ȯ��
			break;
		case2:gradeinput(ifp_g); //2. �����Է�
			break;
		case3:registerInfo(ifp_s); //3. �л��������
			break;
		case4:deleteInfo(); //4. �л���������
			break;
		default: //0. ���α׷� ����
			break;
		};
	}
}
void connect(Student* newNode) {
	if (stu_head == NULL)
	{
		stu_head = newNode;
	}
	else {
		Student* p = stu_head;
		while (p->next != NULL)
			p = p->next;
		p->next = newNode;
	}
}
void registerInfo(FILE* ifp_s) { //3. �л��������
	Student* newNode;

	printf("�л��̸� : ");
	scanf("%s", newNode->name);

	printf("�й� : ");
	scanf("%d", &(newNode->ID));

	printf("��й�ȣ : ");
	scanf("%s", newNode->password);
	connect(newNode);
	fwrite(newNode, sizeof(Student), 1, ifp_s);
}
int gradecheck() { //1. ����Ȯ��
	Grade* grd_tmp;
	Student* stu_tmp;
	int total_credit = 0, total_grade=0, rank=1, cnt=0;
	int ID = 0;
	char password[30];

	printf("�й� : ");
	scanf("%d", ID);

	for (stu_tmp = stu_head; stu_tmp != NULL; stu_tmp = stu_tmp->next) {
		if (stu_tmp->ID==ID) {//���� �й��� ���  
			// �� ... �ٵ� �̷��� �ϸ� �ƴ� ������ ��� ������ ������ ���� ���ٰ� ���� �ʳ�
			printf("������ �й� ������ �����ϴ�!\n");
			return -1;
		}
		else {
			while (1) {
				printf("��й�ȣ : ");
				scanf("%s", password);
				if (password==stu_tmp->password) { //��й�ȣ�� ���� ���
					printf("<%s>���� ����\n", stu_tmp->name);
					while (stu_tmp != NULL) {
						printf("%s : %s\n", grd_tmp->classname, grd_tmp->GPA);
						stu_tmp->total_credit += grd_tmp->credit;
						stu_tmp->average += grd_tmp->grade;
						cnt++;
						// fseek���� �̵��ϴ� �ڵ�
						// ��ü���� �ڵ�
					}
					stu_tmp->average = (stu_tmp->average) / cnt;

					printf("\n�̼����� : %d\n", stu_tmp->total_credit);
					printf("������� : %.1lf\n", stu_tmp->average);
					printf("��ü���� : %d\n", stu_tmp->rank); //���� ���� �ؾ���!!!!!!!!!!!!!!!!!!!!!1
					break;
				}
				else { //��й�ȣ�� Ʋ�� ���
					printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�!\n");
					continue;
				}
			}
			break;
		}
	}
}
int gradeinput(FILE* ifp_g) { //2. �����Է�
	int  num = 0;
	Student* curr;
	curr = stu_head;
	Grade *grd_tmp=(Grade*)malloc(sizeof(Grade)); //���� �Է��ϴ� 
	Student* stu_tmp = (Student*)malloc(sizeof(Student));

	while (1) {
		printf("�й� : ");
		scanf("%d", &(grd_tmp->ID));
		for (curr = stu_head; curr != NULL; curr = curr->next) {
			if (curr->ID == grd_tmp->ID) {
				break;
			}
			else {
				printf("��ϵ� �й��� �ƴմϴ�!\n");
				free(grd_tmp);
				return -1;
			}
		}

		printf("���� : ");
		scanf("%s", grd_tmp->classname);
		
		printf("���� : ");
		while (1) {
			scanf("%d", &(grd_tmp->grade));
			if (grd_tmp->grade >= 0 && grd_tmp->grade <= 100) {
				grd_tmp=gradecheck(grd_tmp, stu_tmp); //�³�....?
				break;
			}
			else {
				printf("1~100 ������ ���� �Է����ּ���.\n");
				continue;
			}
		}
		
		printf("���� : ");
		while (1) {
			scanf("%d", &(grd_tmp->credit));
			if (grd_tmp->credit >= 1 && grd_tmp->credit <= 9) {
				break;
			}
			else { 
				printf("1~9 ������ ���� �Է����ּ���.\n");
				continue;
			}
		}

		fwrite(grd_tmp, sizeof(Grade), 1, ifp_g); //���� �Է�
		printf("������ �� �Է��Ͻ÷��� 1, �׸� �Է� �������� 0�� �Է��Ͻÿ� : ");
		scanf("%d", &num);
		free(grd_tmp);
		free(stu_tmp);
		if (num == 0) {
			break;
		}
		else {
			system("cls");
			continue;
		}
	}
	return 0;
}
int deleteInfo(){
	char key[30];
	int ID = 0;
	char c;
	Student* stu_tmp;
	printf("������ ��й�ȣ : ");
	scanf("%s", key);
	while (1) {
		if (strcmp(key,masterkey)==0) {
			while(1){
				printf("�й�: ");
				scanf("%d", ID);
				for (stu_tmp == stu_head; stu_tmp == NULL; stu_tmp = stu_tmp->next) {
					if (ID == stu_tmp->ID) {
						while (1) {
							printf("<%s>���� ������ �����Ͻðڽ��ϱ�? <y or n>", stu_tmp->name);
							scanf("%c", c);
							if (c == 'y') {
								printf("<%s>���� ������ �����߽��ϴ�!\n", stu_tmp->name);
								stu_tmp; //�ױױױ� ���Ḯ��Ʈ �����ϱ�

								return 0;
							}
							else if (c == 'n') {
								printf("<%s>���� ������ �Ȼ�����\n");
								return 0;
							}
							else {
								printf("y�� n �߿� �Է����ּ���!\n");
								continue;
							}
						}
					}
					else { //�ٵ� �� �̷��� �ϸ�....................�ƴҶ����� ��� ��µǴ¤� �� �ƴϰ�.....
						printf("������ �й� ������ �����ϴ�!\n");
					}
				}
			}
		}
		else { //��й�ȣ�� Ʋ�� ���
			printf("��й�ȣ�� �ùٸ��� �ʽ��ϴ�!\n");
			return -1;
		}
	}

}

Grade* gradecheck(Grade* grd_tmp, Student* stu_tmp) { //���� �Է� -> ����
	if (grd_tmp->grade >= 97 && grd_tmp->grade <= 100) {
		strcpy(grd_tmp->GPA, "A+");
		stu_tmp->total_GPA += 4.5;
	}
	else if (grd_tmp->grade <= 94 && grd_tmp->grade >= 96) {
		strcpy(grd_tmp->GPA, "A0");
		stu_tmp->total_GPA += 4.3;
	}
	else if (grd_tmp->grade <= 90 && grd_tmp->grade >= 93) {
		strcpy(grd_tmp->GPA, "A-");
		stu_tmp->total_GPA += 4.0;
	}
	else if (grd_tmp->grade <= 87 && grd_tmp->grade >= 89) {
		strcpy(grd_tmp->GPA, "B+");
		stu_tmp->total_GPA += 3.5;
	}
	else if (grd_tmp->grade <= 84 && grd_tmp->grade >= 86) {
		strcpy(grd_tmp->GPA, "B0");
		stu_tmp->total_GPA += 3.3;
	}
	else if (grd_tmp->grade <= 80 && grd_tmp->grade >= 83) {
		strcpy(grd_tmp->GPA, "B-");
		stu_tmp->total_GPA += 3.0;
	}
	else if (grd_tmp->grade <= 77 && grd_tmp->grade >= 79) {
		strcpy(grd_tmp->GPA, "C+");
		stu_tmp->total_GPA += 2.5;
	}
	else if (grd_tmp->grade <= 74 && grd_tmp->grade >= 76) {
		strcpy(grd_tmp->GPA, "C0");
		stu_tmp->total_GPA += 2.3
	}
	else if (grd_tmp->grade <= 70 && grd_tmp->grade >= 73) {
		strcpy(grd_tmp->GPA, "C-");
		stu_tmp->total_GPA += 2.0;
	}
	else if (grd_tmp->grade <= 67 && grd_tmp->grade >= 69) {
		strcpy(grd_tmp->GPA, "D+");
		stu_tmp->total_GPA += 1.5;
	}
	else if (grd_tmp->grade <= 64 && grd_tmp->grade >= 66) {
		strcpy(grd_tmp->GPA, "D0");
		stu_tmp->total_GPA += 1.3;
	}
	else if (grd_tmp->grade <= 60 && grd_tmp->grade >= 63) {
		strcpy(grd_tmp->GPA, "D-");
		stu_tmp->total_GPA += 1.0;
	}
	else {
		strcpy(grd_tmp->GPA, "F");
		stu_tmp->total_GPA += 0;
	}
	return grd_tmp;
}
