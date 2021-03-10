#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct student {
	char name[20]; //�л��̸�
	int ID; //�й�
	char password[30]; //��й�ȣ

	int total_credit; //�� �̼�����
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
void gradecheck() { //1. ����Ȯ��
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
		}
		else {
			while (1) {
				printf("��й�ȣ : ");
				scanf("%s", password);
				if (password==stu_tmp->password) { //��й�ȣ�� ���� ���
					printf("<%s>���� ����\n", stu_tmp->name);
					while (stu_tmp != NULL) {
						printf("%s : %s\n", grd_tmp->classname, grd_tmp->grade);
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
	Grade *tmp=(Grade*)malloc(sizeof(Grade)); //���� �Է��ϴ� 
	while (1) {
		printf("�й� : ");
		scanf("%d", &(tmp->ID));
		for (curr = stu_head; curr != NULL; curr = curr->next) {
			if (curr->ID == tmp->ID) {
				break;
			}
			else {
				printf("������ �й� ������ �����ϴ�!\n");
				free(tmp);
				return -1;
			}
		}

		printf("���� : ");
		scanf("%s", tmp->classname);
		
		printf("���� : ");
		while (1) {
			scanf("%d", &(tmp->grade));
			if (tmp->grade >= 0 && tmp->grade <= 100) {
				tmp=gradecheck(tmp); //�³�....?
				break;
			}
			else {
				printf("1~100 ������ ���� �Է����ּ���.\n");
				continue;
			}
		}
		
		printf("���� : ");
		while (1) {
			scanf("%d", &(tmp->credit));
			if (tmp->credit >= 1 && tmp->credit <= 9) {
				break;
			}
			else { 
				printf("1~9 ������ ���� �Է����ּ���.\n");
				continue;
			}
		}

		fwrite(tmp, sizeof(Grade), 1, ifp_g); //���� �Է�
		printf("������ �� �Է��Ͻ÷��� 1, �׸� �Է� �������� 0�� �Է��Ͻÿ� : ");
		scanf("%d", &num);
		free(tmp);
		if (num == 0) {
			break;
		}
		else {
			continue;
		}
	}
	return 0;
}

void deleteInfo(){

}

Grade* gradecheck(Grade* tmp) { //���� �Է� -> ����
	if (tmp->grade >= 97 && tmp->grade <= 100) {
		strcpy(tmp->GPA, "A+");
	}
	else if (tmp->grade <= 94 && tmp->grade >= 96) {
		strcpy(tmp->GPA, "A0");
	}
	else if (tmp->grade <= 90 && tmp->grade >= 93) {
		strcpy(tmp->GPA, "A-");
	}
	else if (tmp->grade <= 87 && tmp->grade >= 89) {
		strcpy(tmp->GPA, "B+");
	}
	else if (tmp->grade <= 84 && tmp->grade >= 86) {
		strcpy(tmp->GPA, "B0");
	}
	else if (tmp->grade <= 80 && tmp->grade >= 83) {
		strcpy(tmp->GPA, "B-");
	}
	else if (tmp->grade <= 77 && tmp->grade >= 79) {
		strcpy(tmp->GPA, "C+");
	}
	else if (tmp->grade <= 74 && tmp->grade >= 76) {
		strcpy(tmp->GPA, "C0");
	}
	else if (tmp->grade <= 70 && tmp->grade >= 73) {
		strcpy(tmp->GPA, "C-");
	}
	else if (tmp->grade <= 67 && tmp->grade >= 69) {
		strcpy(tmp->GPA, "D+");
	}
	else if (tmp->grade <= 64 && tmp->grade >= 66) {
		strcpy(tmp->GPA, "D0");
	}
	else if (tmp->grade <= 60 && tmp->grade >= 63) {
		strcpy(tmp->GPA, "D-");
	}
	else {
		strcpy(tmp->GPA, "F");
	}
	return tmp;
}
