#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>

#define QUESTION_SIZE 1024
#define ANSWER_SIZE 512

//전역 변수. 
int g_question_num;

//함수 선언.
void decideMenu();
void getQuestion();
void saveQuestion(char get_question[], char get_answer[]);
int enterInteger();
int getQuestionNumber();
void solveQuestion(int get_score, int get_question_num, int get_coincide_question_count);
void openQuestionFile(int get_score, int get_question_num, int get_coincide_question_count);
void checkAnswer(char *get_cut_answer, int get_score, int get_question_num, int get_coincide_question_count);
void viewEncourage(int get_score);
void viewExplanation();
void startIntroduction();

//시작.
int main()
{
	//g_question_num(전역 변수)
	FILE *start_question_file;
	char check_line;
	g_question_num = 1;
	
	start_question_file = fopen("..\\Programming\\saves\\makeUserQuestionFile.txt","a");
	
	if(start_question_file != NULL)
	{
		start_question_file = fopen("..\\Programming\\saves\\makeUserQuestionFile.txt","r");
		
		while((check_line = fgetc(start_question_file)) != EOF)
		{
			if(check_line == '\n')
			{
				g_question_num++;
			}
		}
		fclose(start_question_file);
	}
	else
	{
		start_question_file = fopen("..\\Programming\\saves\\makeUserQuestionFile.txt","a");
		fclose(start_question_file);
	}
		
	decideMenu();
}

void decideMenu()
{
	system("cls");
	startIntroduction();
	viewExplanation();

	int Coincide_question_count = 0;
	int score = 0;
		
	printf("\n\n선택해 주세요 : ");

	switch(getch())
	{
		case '1':	
				getQuestion();
				break;						
		case '2':											
				solveQuestion(score, getQuestionNumber(), Coincide_question_count);
				break;
		case '3':
				printf("\n\n종료합니다.");
				exit(1);
				break;	
		default:
				printf("\n\n입력을 읽을 수가 없습니다! 선택사항만 입력 해주세요!");
				getch();
				decideMenu();
				break;
	}				
}

void getQuestion()
{	
	char enter_question[QUESTION_SIZE] = {'\0'};
	char enter_answer[ANSWER_SIZE] = {'\0'};
	
	system("cls");
	printf("<문제 입력>");	
	
	printf("\n문제를 작성하세요 : ");
	gets(enter_question);
	
	printf("\n정답을 작성하세요 : ");	
	gets(enter_answer);
	
	if(enter_question[0] == '\0' || enter_answer[0] == '\0')
	{
		printf("\n공백은 저장을 못 합니다!\n\n아무 키나 누르면 돌아갑니다.");
		getch();
		decideMenu();
	}
	else
	{
		printf("\n*주의*\n아무 키나 누르면 저장이 안 되고 나가집니다.\n\n저장하시려면 (y)키를 누르세요 : ");
			
		if(getch() == 'y')
		{
			saveQuestion(enter_question, enter_answer);
		}
		else
		{
			decideMenu();	
		}
	}										
}

void saveQuestion(char get_question[], char get_answer[])
{	
	//g_question_num(전역 변수)
	FILE *save_question_to_file;

	save_question_to_file = fopen("..\\Programming\\saves\\makeUserQuestionFile.txt","a");
	fprintf(save_question_to_file, "[%d번 문제] %s|%s|\n", g_question_num, get_question, get_answer);
	g_question_num++;
	fclose(save_question_to_file);
	decideMenu();
}

int getQuestionNumber()
{	
	//g_question_num(전역 변수)
	int get_question_num = 0;
		
	system("cls");
	
	if(g_question_num - 1 < 10)
	{		
		printf("\n문제를 더 작성해 주세요!\n");
		printf("\n채워야 할 문제 수 : 10문제 이상\n");
		printf("\n현재 만들어진 문제 수 : %d문제\n", g_question_num - 1);
		printf("\n아무 키나 누르시면 돌아갑니다.");
		getch();
		decideMenu();
	}
	
	printf("<문제 풀기>\n");
	printf("\n원하시는 문제 수를 입력하세요 : ");
	get_question_num = enterInteger();
				
	if(get_question_num == 0 || get_question_num > 100)
	{		
		printf("\n입력을 읽을 수가 없습니다!\n\n100보다 작은 수를 입력하시거나, 정수만 입력하십시오.\n");
		printf("\n아무 키나 누르시면 돌아갑니다.");
		getch();
		decideMenu();
	}
	else
	{
		return get_question_num;
	}		
}

void solveQuestion(int get_score, int get_question_num, int get_coincide_question_count)
{				
	system("cls");
	printf("<문제 풀기>\n");			
	printf("\n현재 점수 : %d점 \t남은 문제 수 :  %d개\t현재 정답 수 : %d개\n", get_score, get_question_num, get_coincide_question_count);
	
	if(get_question_num > 0)
	{
		get_question_num--;
		openQuestionFile(get_score, get_question_num, get_coincide_question_count);		
	}
	else
	{
		viewEncourage(get_score);
		printf("\n\n모든 문제를 다 풀었습니다.");
		printf("\n아무 키나 누르시면 메뉴로 돌아갑니다.");
		getch();
		decideMenu();
	}						
}

void openQuestionFile(int get_score, int get_question_num, int get_coincide_question_count)
{
	//g_question_num(전역 변수)
	srand((unsigned)time(NULL));
	
	char view_question[QUESTION_SIZE] = {0};
	
	char *cut_question;
	char *cut_answer;
	
	int i;
	int random;
	
	FILE *open_question_file;
	open_question_file = fopen("..\\Programming\\saves\\makeUserQuestionFile.txt","r");
	
    random = rand() % g_question_num + 1;
    
	for(i = 0; i < random; i++)
	{
		fgets(view_question, QUESTION_SIZE, open_question_file);
	}		
	
	cut_question = strtok(view_question, "|");
	printf("\n%s\n", cut_question);
	cut_answer = strtok(NULL, "|");
	checkAnswer(cut_answer, get_score, get_question_num, get_coincide_question_count);
	fclose(open_question_file);
}

void checkAnswer(char *get_cut_answer, int get_score, int get_question_num, int get_coincide_question_count)
{
	char enter_answer[ANSWER_SIZE] = {};
	printf("\n답을 입력하세요 : ");		
	gets(enter_answer);	

	if(strcmp(enter_answer, get_cut_answer) == 0)
	{
		printf("\n정답입니다!\n");
		get_coincide_question_count++;
		get_score += 5;
	}
	else
	{
		printf("\n답이 아닙니다!\n");				
		
		if(get_score > 0)
		{
			get_score -= 5;
		}
		else
		{
			get_score = 0;
		}
		printf("\n정답 : %s\n", get_cut_answer);								
	}
	    	    
    printf("\n[ESC]를 눌러 나가시거나, 아무 키를 눌러 다음 문제로 이동하십시오.");
	if(getch() == 27)
	{
		decideMenu();
	}
	else
	{
		solveQuestion(get_score, get_question_num, get_coincide_question_count);	
	}	
}

void viewEncourage(int get_score)
{
	if(get_score == 100)
	{
		printf("지금처럼만 하십시오!!!");
	}
	else if(get_score >= 90)
	{
		printf("조금만 더 노력해서 좋은 결과 만듭시다!!!");
	}
	else if(get_score >= 75)
	{
		printf("지금보다 분발하시면 더 좋은 결과가 있을겁니다!!");
	}
	else if(get_score >= 50)
	{
		printf("노력합시다! 노력하면 안 되는게 없습니다!!");
	}
	else if(get_score >= 20)
	{
		printf("분발하시길 바랍니다.");
	}
	else
	{
		printf("공부를 하시고 문제를 푸시길 바랍니다.");
	}
}

void viewExplanation()
{		
	printf("<설명>\n\n");
	printf("문제는 저장하실 수 있고, 저장하신 문제를 푸실 때는 문제가 무작위로 나옵니다.\n\n");
	printf("[1] 문제 작성\n\n");
	printf("[2] 문제 풀이\n\n");
	printf("[3] 프로그램 종료\n\n");
	printf("============================================================");
	printf("============================================================");		
}

void startIntroduction()
{
	printf("\n이 프로그램은 문제를 직접 만들고 공부하고 ");
	printf("자신이 얼마나 공부가 잘 되었는지를 테스트 ");
	printf("할 수 있는 프로그램으로 \n자신이 문제를 ");
	printf("작성하고 또 그 문제를 풀어가며 자신의 능력치를 ");
	printf("키워갈 수 있는 프로그램입니다.\n\n");
	printf("제작자 - 10712 원준서\n");
	printf("============================================================");
	printf("============================================================\n");
}

int enterInteger()
{
	char num_str[3] = {};
	int num = 0;
	int i;
	
	gets(num_str);
	
	for(i = 0; i < strlen(num_str); i++)
	{	
		if(isdigit(num_str[i]) != 0)
		{
			num = num * 10 + num_str[i] - '0';
		}
		else
		{
			num = 0;
			break;
		}		
	}
	return num;
}
