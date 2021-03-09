//���Ḯ��Ʈ��......����......������� ���ٴ�...........

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct student {
	char name[20]; //�л��̸�
	int ID; //�й�
	char password[30]; //��й�ȣ
	struct student* next;
}Student;

typedef struct grade {
	int ID; //�й�
	char classname[20]; //�����̸�
	int grade; //����
	int credit; //����
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

void registerInfo(FILE* ifp_s) {
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
void gradecheck() {
	Grade* tmp_grade;
	Student* tmp_std;
	int total_credit = 0, total_grade=0, rank=1, cnt=0;
	int ID = 0;
	char password[30];

	printf("�й� : ");
	scanf("%d", ID);

	if (ID) {//���� �й��� ���
		printf("������ �й� ������ �����ϴ�!\n");
	}
	else {
		while (1) {
			printf("��й�ȣ : ");
			scanf("%s", password);
			if (password) { //��й�ȣ�� ���� ���
				printf("<%s>���� ����\n", tmp_std->name);
				while (tmp_grade != NULL) {
					printf("%s : %s\n", tmp_grade->classname, tmp_grade->grade);
					total_credit += *(tmp_grade->credit);
					total_grade += *(tmp_grade->grade);
					cnt++;
					// fseek���� �̵��ϴ� �ڵ�
					// ��ü���� �ڵ�
				}

				printf("\n�̼����� : %d\n", total_credit);
				printf("������� : %.1lf\n", (double)total_grade / cnt);
				printf("��ü���� : %d\n", rank);
				break;
			}
			else { //��й�ȣ�� Ʋ�� ���
				printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�!\n");
			}
		}
	}
}


int gradeinput(FILE* ifp_g) {
	int  num = 0;
	Student* curr;
	curr = stu_head;
	Grade *tmp=(Grade*)malloc(sizeof(Grade));
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
		fwrite(tmp, sizeof(Grade), 1, ifp_g);
		printf("������ �� �Է��Ͻ÷��� 1, �׸� �Է� �������� 0�� �Է��Ͻÿ� : ");
		scanf("%d", &num);
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



//void gradecheck(char* curr, int grade) { //���� �Է� -> ����
//	if (grade >= 97 && grade <= 100) {
//		strcpy(curr, "A+");
//	}
//	else if (grade <= 94 && grade >= 96) {
//		strcpy(curr, "A0");
//	}
//	else if (grade <= 90 && grade >= 93) {
//		strcpy(curr, "A-");
//	}
//	else if (grade <= 87 && grade >= 89) {
//		strcpy(curr, "B+");
//	}
//	else if (grade <= 84 && grade >= 86) {
//		strcpy(curr, "B0");
//	}
//	else if (grade <= 80 && grade >= 83) {
//		strcpy(curr, "B-");
//	}
//	else if (grade <= 77 && grade >= 79) {
//		strcpy(curr, "C+");
//	}
//	else if (grade <= 74 && grade >= 76) {
//		strcpy(curr, "C0");
//	}
//	else if (grade <= 70 && grade >= 73) {
//		strcpy(curr, "C-");
//	}
//	else if (grade <= 67 && grade >= 69) {
//		strcpy(curr, "D+");
//	}
//	else if (grade <= 64 && grade >= 66) {
//		strcpy(curr, "D0");
//	}
//	else if (grade <= 60 && grade >= 63) {
//		strcpy(curr, "D-");
//	}
//	else {
//		strcpy(curr, "F");
//	}
//}
