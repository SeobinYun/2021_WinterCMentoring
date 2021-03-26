#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define USER 1234 // 사용자 비밀번호

typedef struct student{ // 학생정보를 담는 구조체
    char name[50]; // 학생이름
    int code; // 학번
    char psd[20]; // 비밀번호
    struct student *next;
} Student;
   
typedef struct grade{ //성적정보를 담는 구조체
    int code; // 학번
    char class[20]; // 과목명
    char grade[5]; // A+, B+ 학점 저장
    double ave; // 평점저장 4.5 ~
    double realave; // 평점평균 * sum
    double average; // 평점평균
    int abcf; // 몇학점? 
    int sum; // 석차계산용 총 학점 저장 (F포함)
    int sum2; //  에프만 저장
    struct grade *next;
} Grade;

Student *shead, *stail; // 학생정보 구조체의 head, tail
Grade *ghead, *gtail; // 성적정보 구조체의 head, tail
 
void checkgrade(); // 1. 성적확인 함수
void inputgrade(); // 2. 성적입력 함수
void inputstudent(); // 3. 학생정보등록 함수
void delete(); // 4. 학생정보삭제 함수
void transgrade(int, Grade *); // 2-1. 점수를 입력 받은 후 등급으로 변환하는 함수
void ave(Grade *, int); // 2-2. 평점평균계산 함수
int ranking(Grade *); // 1-1. 성적확인하고자 하는 학생의 석차를 계산하는 함수
void myflush(); // scanf()로 값을 입력받은 후 버퍼를 비우는 함수

int main()
{
    int n; // 메뉴 선택 변수 선언
    shead = NULL; // head와 tail을 전부 NULL로 초기화
    stail = NULL;
    ghead = NULL;
    gtail = NULL;

    while(1){ 
        printf("[Menu]\n1. 성적확인  2. 성적입력  3. 학생정보등록  4. 학생정보삭제  0. 프로그램종료\n");
        scanf("%d", &n);
		myflush();

        if(n==0){ // 0. 프로그램 종료
           	printf("프로그램 종료!\n");
		   	break;
        }
        else if(n == 1){ // 1. 성적확인
            checkgrade();
        }
        else if(n == 2){ // 2. 성적입력
            inputgrade();
        }
        else if(n == 3){ // 3. 학생정보 등록
            inputstudent();
        }
        else if(n == 4){ // 4. 학생정보 삭제
            delete();
        }
        else{
            ;
        }
        printf("\n");
    }
    return 0;
}

void checkgrade() //1. 성적확인 함수
{
    Student *scur = shead; // 학생정보를 탐색할 구조체 포인터 선언
    Grade *cur = ghead; // 성적정보를 탐색할 구조체 포인터 선언
    Grade *gcur = (Grade *)malloc(sizeof(Grade)); // 성적 출력에서 쓸 구조체 포인터 
    char pw[20]; // 비밀번호를 입력받을 변수 선언 
    int n, st, rank; // n: 입력받을 학번, st: strcmp함수 리턴값, rank: 
    int a=0; // 학번 유무를 확인하는 변수

    while(1){ // 학번 입력받기
		printf("학번 : ");
		scanf("%d", &n);
		myflush();
		if(n>=10000000 && n<=99999999){ // 학번이 8자리면 while문 탈출
			break;
		}
		else{ // 8자리가 아닐시 8자리를 입력해달라는 문장 출력 후 while문 계속 실행
			printf("8자리 숫자를 입력하여 주세요.\n");
		}
	}

    while(scur != NULL){ // 학번 입력 while문을 탈출한 후 학생정보 연결리스트에 해당 학번 정보가 있는지 확인
        if(scur->code == n){ // 학생정보 연결리스트에 n이라는 해당 학번이 있을 경우
            a++; // 학번이 일치하는 학생이 없으면 a=0 유지: while문 돌지 않고 리턴
            while(a==1){
                printf("비밀번호 : "); 
                scanf("%s", pw);
                myflush();
				st = strcmp(pw, scur->psd);  // strcmp 함수를 이용해 입력받은 pw와 학생정보연결리스트의 비밀번호가 일치하는지 확인 (같을 경우 strcmp 함수 0 리턴)
                if(st == 0){ // 비밀번호가 일치할 경우
                    while(cur != NULL){
                        if(cur->code == n){ //성적정보 연결리스트에서 성적정보가 입력받은 학번과 일치할 경우
                            printf("\n<%s>님의 성적\n", scur->name);
                            cur->realave = 0; 
                            gcur = cur; 
                            while(gcur != NULL){
                                if(gcur->code == n){ //gcur의 학번이 n과 일치할 경우 성적 출력
                                    printf("%s : %s\n", gcur->class, gcur->grade);
                                }
                                gcur = gcur->next;
                            }
                            printf("\n이수학점 : %d\n", cur->sum - cur->sum2);
                            printf("평점평균 : %.1f\n", cur->average); 
                            rank = ranking(cur); //ranking 함수로 석차 정렬
                            printf("전체석차 : %d\n", rank);
                            a++;
                            break;
                        }
                        cur = cur->next;
                    }   
                }
                else{ // 비밀번호가 일치하지 않을 경우
                    printf("비밀번호가 일치하지 않습니다!\n");
                }
            }
            break;
        }
        scur = scur->next; // 학생정보 연결리스트를 탐색하면서 계속 옆으로 넘겨줌
    }
    if(a==0){ // 학생정보가 없을 경우 
        printf("귀하의 학번 정보가 없습니다!\n");
    }
    
    return;
}

void inputgrade() // 2. 성적입력 함수
{
    int n=1; 
    int gr;
    int k=0; 
    while(n == 1){
        Student *scur = shead; // 학생정보 연결리스트를 탐색할 구조체 포인터
        Grade *newNode = (Grade *)malloc(sizeof(Grade)); // 새로 입력할 성적정보
        Grade *cur = ghead; 
        newNode->next = NULL; // 새로 입력할 성적정보의 next를 NULL로 초기화
        int a=0; // 학번 유무 확인할 변수
        int b=0;

        while(1){ // 학번 입력받기
			printf("\n학번 : ");
			scanf("%d", &(newNode->code));
			myflush();
			if(newNode->code>=10000000 && newNode->code<=99999999){
				break;
			}
			else{
				printf("8자리 숫자를 입력하여 주세요.\n");
			}
		}

        while(scur != NULL){ // 학번 입력받은 후 학번유무 확인
            if(newNode->code == scur->code){ // 학번이 있으면 a값을 1로 증가, 학번이 없을 경우 a는 0 유지
                a++;
            }
            scur = scur->next; // 계속 탐색
        }

        if(a==0){ // 학번정보가 없을 경우
            printf("등록된 학번이 아닙니다!\n");
            free(newNode); // 메모리 해제 후 종료
            return;
        }

        printf("과목 : "); // 과목 입력
        scanf("%s", newNode->class);
		myflush();

        while(1){
        	printf("성적 : "); // 성적 입력
			scanf("%d", &gr);
			myflush();
			if(gr>=0 && gr<=100){ // 성적이 0~100 사이일 경우 transgrade()함수를 실행
				transgrade(gr, newNode);
				break;
			} 
			else{ // 아닐 경우 안내문 출력 후 계속 while문 실행
				printf("1~100 사이의 수를 입력해주세요.\n");
			}
		}

        while(1){
        	printf("학점 : "); // 학점 입력
			scanf("%d", &(newNode->abcf));
			myflush();
			if(newNode->abcf >=1 && newNode->abcf<=9){ // 학점이 1~9 사이일 경우 while문 탈출
				break;
			}
			else{ // 아닐 경우 안내문 출력 후 계속 while문 실행
                printf("1~9 사이의 수를 입력해주세요.\n");
			}
		}

        if(ghead == NULL){  
            ghead = newNode;
            newNode->sum = 0; // 이수학점 누적저장(+=)위해 초기화
            newNode->sum2 = 0;
        }
        else{
            gtail->next = newNode;
        }
        gtail = newNode;

        while(cur != NULL){
            if(newNode->code == cur->code){
                cur->sum += newNode->abcf;
                if(newNode->ave == 0.0){  // F학점 저장
                    cur->sum2 += newNode->abcf;
                }
                b++;
                break;
            }
            cur = cur->next;
        }

        if(b == 0){
            newNode->sum += newNode->abcf;
            if(newNode->ave == 0.0){
                newNode->sum2 += newNode->abcf;
            }
        }
        ave(newNode, k);

        printf("성적을 더 입력하시려면 1, 그만 입력 받으려면 0을 입력하시오 : ");
        scanf("%d", &n);  
	  	myflush();

        if(n == 1){ 
   			k++;
        }
    }
    return;
}

void inputstudent() //3. 학생정보등록 함수
{
    Student *newNode = (Student *)malloc(sizeof(Student)); // 새로 등록할 학생정보
    newNode->next = NULL;

    if(shead == NULL){ // shead가 NULL일 경우 shead를 newNode로 지정
        shead = newNode;
    }
    else{ // shead가 NULL이 아니면 tail의 next를 newNode로 지정
        stail->next = newNode;
    }
    stail = newNode; // 그 후 newNode를 stail로 지정

    printf("학생이름 : "); // 학생이름 입력
    scanf("%s", newNode->name);
    myflush();

	while(1){
		printf("학번 : ");
		scanf("%d", &(newNode->code));
		myflush();
		if(newNode->code>=10000000 && newNode->code<=99999999){ // 학번 8자리 확인
			break;
		}
		else{
			printf("8자리 숫자를 입력하여 주세요.\n");
		}
	}

    printf("비밀번호 : "); // 비밀번호 입력
    scanf("%s", newNode->psd);
	myflush();

    return;
}

void delete() //4 학생정보삭제
{
    int p, c; // p: 입력받은 비밀번호 저장할 변수, c: 입력받은 학번 저장할 변수
    int s=0; // while문 돌리는 변수
    char yorn; // 정보 삭제할지 말지 yes or no
    Student *curs = shead;
    Student *prev = (Student *)malloc(sizeof(Student));
    Grade *gcur = ghead;
    Grade *gprev = (Grade *)malloc(sizeof(Grade));

    printf("관리자 비밀번호 : "); // 관리자 비밀번호 입력받음 
    scanf("%d", &p);
    myflush();

	if(p != USER){ // p가 관리자 비밀번호와 일치하지 않을 경우
        printf("비밀번호가 일치하지 않습니다!\n");
        return;
    }

    while(s == 0){
        while(1){ // 학번 입력받기
			printf("학번 : ");
			scanf("%d", &c);
			myflush();
			if(c>=10000000 && c<=99999999){
				break;
			}
			else{
				printf("8자리 숫자를 입력하여 주세요.\n");
			}
		}

        while(curs != NULL){ // 입력받은 학번 c가 있는지 확인
            if(c == curs->code){ // 있을 경우 s를 ++하고 while문 탈출 (없을 경우 s는 0이 됨)
                s++;
                break;
            }
            prev = curs; 
            curs = curs->next;  
        }
        if(s != 1){ // 학번정보가 없을 경우
            printf("귀하의 학번정보가 없습니다!\n");
            curs = shead;
        }
    }

    while(gcur != NULL){ // 성적정보 삭제
        if(gcur->code == curs->code){ 
            break;
        }
        gprev = gcur; 
        gcur = gcur->next; 
    }
    
    printf("<%s>님의 정보를 삭제하시겠습니까? <y or n> ", curs->name);
    scanf("%c", &yorn);
	myflush();

    if(yorn == 'y'){ // 삭제를 원할 경우
        if(curs == shead){ 
            shead = curs->next; // 학생정보삭제
            ghead = gcur->next; // 성적삭제
        }
        else{
            prev->next = curs->next; //학생정보삭제
            gprev->next = gcur->next; //성적삭제
        }
        printf("<%s>님의 정보를 삭제했습니다!\n", curs->name);
        curs = curs->next; 
        gcur = gcur->next; 
    }
    else if(yorn == 'n'){ // 삭제를 원하지 않는 경우
        printf("<%s>님의 정보를 삭제하지 않았습니다!\n", curs->name);
    }
    else{ // y 또는 n이 아닌 값을 받을 경우
        printf("잘못된 입력입니다!\n");
        return;
    }

    return;
}

void transgrade(int n, Grade *Node)
{
    if(n>=97 && n<=100){ 
        strcpy(Node->grade, "A+");
        Node->ave = 4.5;
    }
    else if(n<97 && n>93){
        strcpy(Node->grade, "A0");
        Node->ave = 4.3;
    }
    else if(n<94 && n>=90){
        strcpy(Node->grade, "A-");
        Node->ave = 4.0;
    }
    else if(n<90 && n>=87){
        strcpy(Node->grade, "B+");
        Node->ave = 3.5;
    }
    else if(n<87 && n>=84){
        strcpy(Node->grade, "B0");
        Node->ave = 3.3;
    }
    else if(n<84 && n>=80){
        strcpy(Node->grade, "B-");
        Node->ave = 3.0;
    }
    else if(n<80 && n>=77){
        strcpy(Node->grade, "C+");
        Node->ave = 2.5;
    }
    else if(n<77 && n>=74){
        strcpy(Node->grade, "C0");
        Node->ave = 2.3;
    }
    else if(n<74 && n>=70){
        strcpy(Node->grade, "C-");
        Node->ave = 2.0;
    }
    else if(n<70 && n>=67){
        strcpy(Node->grade, "D+");
        Node->ave = 1.5;
    }
    else if(n<67 && n>=64){
        strcpy(Node->grade, "D0");
        Node->ave = 1.3;
    }
    else if(n<64 && n>=60){
        strcpy(Node->grade, "D-");
        Node->ave = 1.0;
    }
    else if(n<60){
        strcpy(Node->grade, "F");
        Node->ave = 0.0;
    }
    else{
        ;
    }
    return;
}

void ave(Grade *cur, int n) //평점평균계산 함수
{
    int a=0;
    Grade *gcur = ghead;
    while(gcur != NULL){ 
        if(gcur->code == cur->code && gcur->next != NULL){
            if(n == 0){
                gcur->realave += gcur->average*(gcur->sum-cur->abcf);
            }
            gcur->realave += (cur->abcf)*(cur->ave);
            gcur->average = (gcur->realave)/(gcur->sum);
            a++;
            break;
        }
        gcur = gcur->next;
    }
    if(a == 0){
        cur->realave = (cur->ave)*(cur->abcf);
        cur->average = (cur->realave)/(cur->sum);
    }

    return;
}

int ranking(Grade *cur) // 석차정렬 함수
{
    int r=1; 
    Grade *gcur = ghead;
    while(gcur != NULL){
        if(cur->average < gcur->average){
            r++;
        }
        else if(cur->average == gcur->average){
            if(cur->sum < gcur->sum){
                r++;
            }
        }
        else{
            ;
        }
        gcur = gcur->next;
    }

    return r;
}

void myflush() // scanf()로 값을 입력받은 후 버퍼를 비우는 함수
{
    while(getchar() != '\n'){ // Enter가 입력될 때까지 getchar()로 버퍼 비움
        ;
    }
}

