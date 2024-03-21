#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>

#define QUESTION_SIZE 1024
#define ANSWER_SIZE 512

//���� ����. 
int g_question_num;

//�Լ� ����.
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

//����.
int main()
{
	//g_question_num(���� ����)
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
		
	printf("\n\n������ �ּ��� : ");

	switch(getch())
	{
		case '1':	
				getQuestion();
				break;						
		case '2':											
				solveQuestion(score, getQuestionNumber(), Coincide_question_count);
				break;
		case '3':
				printf("\n\n�����մϴ�.");
				exit(1);
				break;	
		default:
				printf("\n\n�Է��� ���� ���� �����ϴ�! ���û��׸� �Է� ���ּ���!");
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
	printf("<���� �Է�>");	
	
	printf("\n������ �ۼ��ϼ��� : ");
	gets(enter_question);
	
	printf("\n������ �ۼ��ϼ��� : ");	
	gets(enter_answer);
	
	if(enter_question[0] == '\0' || enter_answer[0] == '\0')
	{
		printf("\n������ ������ �� �մϴ�!\n\n�ƹ� Ű�� ������ ���ư��ϴ�.");
		getch();
		decideMenu();
	}
	else
	{
		printf("\n*����*\n�ƹ� Ű�� ������ ������ �� �ǰ� �������ϴ�.\n\n�����Ͻ÷��� (y)Ű�� �������� : ");
			
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
	//g_question_num(���� ����)
	FILE *save_question_to_file;

	save_question_to_file = fopen("..\\Programming\\saves\\makeUserQuestionFile.txt","a");
	fprintf(save_question_to_file, "[%d�� ����] %s|%s|\n", g_question_num, get_question, get_answer);
	g_question_num++;
	fclose(save_question_to_file);
	decideMenu();
}

int getQuestionNumber()
{	
	//g_question_num(���� ����)
	int get_question_num = 0;
		
	system("cls");
	
	if(g_question_num - 1 < 10)
	{		
		printf("\n������ �� �ۼ��� �ּ���!\n");
		printf("\nä���� �� ���� �� : 10���� �̻�\n");
		printf("\n���� ������� ���� �� : %d����\n", g_question_num - 1);
		printf("\n�ƹ� Ű�� �����ø� ���ư��ϴ�.");
		getch();
		decideMenu();
	}
	
	printf("<���� Ǯ��>\n");
	printf("\n���Ͻô� ���� ���� �Է��ϼ��� : ");
	get_question_num = enterInteger();
				
	if(get_question_num == 0 || get_question_num > 100)
	{		
		printf("\n�Է��� ���� ���� �����ϴ�!\n\n100���� ���� ���� �Է��Ͻðų�, ������ �Է��Ͻʽÿ�.\n");
		printf("\n�ƹ� Ű�� �����ø� ���ư��ϴ�.");
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
	printf("<���� Ǯ��>\n");			
	printf("\n���� ���� : %d�� \t���� ���� �� :  %d��\t���� ���� �� : %d��\n", get_score, get_question_num, get_coincide_question_count);
	
	if(get_question_num > 0)
	{
		get_question_num--;
		openQuestionFile(get_score, get_question_num, get_coincide_question_count);		
	}
	else
	{
		viewEncourage(get_score);
		printf("\n\n��� ������ �� Ǯ�����ϴ�.");
		printf("\n�ƹ� Ű�� �����ø� �޴��� ���ư��ϴ�.");
		getch();
		decideMenu();
	}						
}

void openQuestionFile(int get_score, int get_question_num, int get_coincide_question_count)
{
	//g_question_num(���� ����)
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
	printf("\n���� �Է��ϼ��� : ");		
	gets(enter_answer);	

	if(strcmp(enter_answer, get_cut_answer) == 0)
	{
		printf("\n�����Դϴ�!\n");
		get_coincide_question_count++;
		get_score += 5;
	}
	else
	{
		printf("\n���� �ƴմϴ�!\n");				
		
		if(get_score > 0)
		{
			get_score -= 5;
		}
		else
		{
			get_score = 0;
		}
		printf("\n���� : %s\n", get_cut_answer);								
	}
	    	    
    printf("\n[ESC]�� ���� �����ðų�, �ƹ� Ű�� ���� ���� ������ �̵��Ͻʽÿ�.");
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
		printf("����ó���� �Ͻʽÿ�!!!");
	}
	else if(get_score >= 90)
	{
		printf("���ݸ� �� ����ؼ� ���� ��� ����ô�!!!");
	}
	else if(get_score >= 75)
	{
		printf("���ݺ��� �й��Ͻø� �� ���� ����� �����̴ϴ�!!");
	}
	else if(get_score >= 50)
	{
		printf("����սô�! ����ϸ� �� �Ǵ°� �����ϴ�!!");
	}
	else if(get_score >= 20)
	{
		printf("�й��Ͻñ� �ٶ��ϴ�.");
	}
	else
	{
		printf("���θ� �Ͻð� ������ Ǫ�ñ� �ٶ��ϴ�.");
	}
}

void viewExplanation()
{		
	printf("<����>\n\n");
	printf("������ �����Ͻ� �� �ְ�, �����Ͻ� ������ Ǫ�� ���� ������ �������� ���ɴϴ�.\n\n");
	printf("[1] ���� �ۼ�\n\n");
	printf("[2] ���� Ǯ��\n\n");
	printf("[3] ���α׷� ����\n\n");
	printf("============================================================");
	printf("============================================================");		
}

void startIntroduction()
{
	printf("\n�� ���α׷��� ������ ���� ����� �����ϰ� ");
	printf("�ڽ��� �󸶳� ���ΰ� �� �Ǿ������� �׽�Ʈ ");
	printf("�� �� �ִ� ���α׷����� \n�ڽ��� ������ ");
	printf("�ۼ��ϰ� �� �� ������ Ǯ��� �ڽ��� �ɷ�ġ�� ");
	printf("Ű���� �� �ִ� ���α׷��Դϴ�.\n\n");
	printf("������ - 10712 ���ؼ�\n");
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
