//할일
//1. 석차 정렬
//2. 삭제
//3. 성적입력에서 Grade 파일 업데이트 시 학번 기준으로 정렬 저장하는거
//4. 연결리스트 됐는지 확인
//5. 평점 평균

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
typedef struct student {
	char name[20]; //학생이름
	int ID; //학번
	char password[30]; //비밀번호

	int total_credit; //총 이수학점
	double total_GPA; //총 평점
	double average; // 평점평균
	int rank; //전체석차
	struct student* next;
}Student;

typedef struct grade {
	int ID; //학번
	char classname[20]; //과목이름
	int grade; //성적
	int credit; //이수학점
	char GPA[3]; //학점 ex) A+
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
		printf("[ Menu ]\n1. 성적확인\t2. 성적입력\t3. 학생정보등록\t4. 학생정보삭제\t0. 프로그램 종료\n");
		scanf("%d", &res);
		switch (res) {
		case1:gradecheck(); //1. 성적확인
			break;
		case2:gradeinput(ifp_g); //2. 성적입력
			break;
		case3:registerInfo(ifp_s); //3. 학생정보등록
			break;
		case4:deleteInfo(); //4. 학생정보삭제
			break;
		default: //0. 프로그램 종료
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
void registerInfo(FILE* ifp_s) { //3. 학생정보등록
	Student* newNode;

	printf("학생이름 : ");
	scanf("%s", newNode->name);

	printf("학번 : ");
	scanf("%d", &(newNode->ID));

	printf("비밀번호 : ");
	scanf("%s", newNode->password);
	connect(newNode);
	fwrite(newNode, sizeof(Student), 1, ifp_s);
}
int gradecheck() { //1. 성적확인
	Grade* grd_tmp;
	Student* stu_tmp;
	int total_credit = 0, total_grade=0, rank=1, cnt=0;
	int ID = 0;
	char password[30];

	printf("학번 : ");
	scanf("%d", ID);

	for (stu_tmp = stu_head; stu_tmp != NULL; stu_tmp = stu_tmp->next) {
		if (stu_tmp->ID==ID) {//없는 학번일 경우  
			// 어 ... 근데 이렇게 하면 아닐 때마다 계속 귀하의 ㅎㄱ번 정보 없다고 뜨지 않나
			printf("귀하의 학번 정보가 없습니다!\n");
			return -1;
		}
		else {
			while (1) {
				printf("비밀번호 : ");
				scanf("%s", password);
				if (password==stu_tmp->password) { //비밀번호가 맞을 경우
					printf("<%s>님의 성적\n", stu_tmp->name);
					while (stu_tmp != NULL) {
						printf("%s : %s\n", grd_tmp->classname, grd_tmp->GPA);
						stu_tmp->total_credit += grd_tmp->credit;
						stu_tmp->average += grd_tmp->grade;
						cnt++;
						// fseek으로 이동하는 코드
						// 전체석차 코드
					}
					stu_tmp->average = (stu_tmp->average) / cnt;

					printf("\n이수학점 : %d\n", stu_tmp->total_credit);
					printf("평점평균 : %.1lf\n", stu_tmp->average);
					printf("전체석차 : %d\n", stu_tmp->rank); //성적 정렬 해야함!!!!!!!!!!!!!!!!!!!!!1
					break;
				}
				else { //비밀번호가 틀릴 경우
					printf("비밀번호가 일치하지 않습니다!\n");
					continue;
				}
			}
			break;
		}
	}
}
int gradeinput(FILE* ifp_g) { //2. 성적입력
	int  num = 0;
	Student* curr;
	curr = stu_head;
	Grade *grd_tmp=(Grade*)malloc(sizeof(Grade)); //새로 입력하는 
	Student* stu_tmp = (Student*)malloc(sizeof(Student));

	while (1) {
		printf("학번 : ");
		scanf("%d", &(grd_tmp->ID));
		for (curr = stu_head; curr != NULL; curr = curr->next) {
			if (curr->ID == grd_tmp->ID) {
				break;
			}
			else {
				printf("등록된 학번이 아닙니다!\n");
				free(grd_tmp);
				return -1;
			}
		}

		printf("과목 : ");
		scanf("%s", grd_tmp->classname);
		
		printf("성적 : ");
		while (1) {
			scanf("%d", &(grd_tmp->grade));
			if (grd_tmp->grade >= 0 && grd_tmp->grade <= 100) {
				grd_tmp=gradecheck(grd_tmp, stu_tmp); //맞나....?
				break;
			}
			else {
				printf("1~100 사이의 수를 입력해주세요.\n");
				continue;
			}
		}
		
		printf("학점 : ");
		while (1) {
			scanf("%d", &(grd_tmp->credit));
			if (grd_tmp->credit >= 1 && grd_tmp->credit <= 9) {
				break;
			}
			else { 
				printf("1~9 사이의 수를 입력해주세요.\n");
				continue;
			}
		}

		fwrite(grd_tmp, sizeof(Grade), 1, ifp_g); //파일 입력
		printf("성적을 더 입력하시려면 1, 그만 입력 받으려면 0을 입력하시오 : ");
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
	printf("관리자 비밀번호 : ");
	scanf("%s", key);
	while (1) {
		if (strcmp(key,masterkey)==0) {
			while(1){
				printf("학번: ");
				scanf("%d", ID);
				for (stu_tmp == stu_head; stu_tmp == NULL; stu_tmp = stu_tmp->next) {
					if (ID == stu_tmp->ID) {
						while (1) {
							printf("<%s>님의 정보를 삭제하시겠습니까? <y or n>", stu_tmp->name);
							scanf("%c", c);
							if (c == 'y') {
								printf("<%s>님의 정보를 삭제했습니다!\n", stu_tmp->name);
								stu_tmp; //그그그그 연결리스트 삭제하기

								return 0;
							}
							else if (c == 'n') {
								printf("<%s>님의 정보를 안삭제함\n");
								return 0;
							}
							else {
								printf("y랑 n 중에 입력해주세요!\n");
								continue;
							}
						}
					}
					else { //근데 또 이렇게 하면....................아닐때마다 계속 출력되는ㄱ ㅓ 아니가.....
						printf("귀하의 학번 정보가 없습니다!\n");
					}
				}
			}
		}
		else { //비밀번호가 틀릴 경우
			printf("비밀번호가 올바르지 않습니다!\n");
			return -1;
		}
	}

}

Grade* gradecheck(Grade* grd_tmp, Student* stu_tmp) { //성적 입력 -> 학점
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
