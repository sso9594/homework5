/* postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	printf("[----- [Your Name] [Student ID] -----]\n");
	printf("\t2019038073  신승용\n");
	char command;

	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
	postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
	char x;
	if (postfixStackTop == -1)
		return '\0';
	else {
		x = postfixStack[postfixStackTop--];
	}
	return x;
}

void evalPush(int x)
{
	evalStack[++evalStackTop] = x;
}

int evalPop()
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}

precedence getToken(char symbol)
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0')
	{
		/* 필요한 로직 완성 */
		if (getPriority(*exp) == operand)	// 입력받은 exp를 getPriority()함수에 넣어 리턴값으로 operand를 받으면 exp가 피연산자 일 경우이다.
		{
			x = *exp;	// exp가 가리키고 있는 곳의 값을 x로 복사
			charCat(&x);	// charCat() 함수를 이용하여 postfixExp에 추가한다.
		}
		else if (getPriority(*exp) == lparen) {	// 입력받은 exp를 getPriority()함수에 넣어 리턴값으로 lparen을 받으면 exp가 왼쪽 괄호 일 경우이다.

			postfixPush(*exp);	// 왼쪽괄호 문자를 postfixPush() 함수를 이용하여 postfixStack의 Top에 입력한다.
		}
		else if (getPriority(*exp) == rparen)	// 입력받은 exp를 getPriority()함수에 넣어 리턴값으로 rparen을 받으면 exp가 오른쪽 괄호일 경우이다.
		{
			while ((x = postfixPop()) != '(') {	// 왼쪽괄호가 나올 때 까지 반복한다.
				charCat(&x);	// charCat() 함수를 이용하여 왼쪽 괄호가 나올 때 까지 postfixStack을 pop 시켜 postfixExp에 입력한다.
			}
		}
		else // getPriority(*exp)가 사칙연산 기호 일 경우
		{
			while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))	// postfixStack[postfixStackTop]의 우선순위가 *exp의 우선순위보다 클때 까지 반복. 연산자마다 우선순위가 있기 때문에 스택에 있는 연산자와 *exp의 연산자를 비교한다.
			{
				x = postfixPop();	// postfixStack에 있는 연산자가 우선순위가 클경우
				charCat(&x);	// postfixStack에서 pop을 시킨다.
			}
			postfixPush(*exp);	// 연산자 문자를 postfixPush() 함수를 이용하여 postfixStack의 Top에 입력한다.
		}
		exp++;

	}

	/* 필요한 로직 완성 */
	while (postfixStackTop != -1)	// postfixStackTop이 -1이 아닐경우 반복, 입력 값은 우선순위대로 순서대로 입력되어있음. postfixStack에 있는 값들을 후위표기식으로 postfixExp에 입력하기 위한 반복문
	{
		x = postfixPop();	// postfixStack에 있는 값을 pop 한다.
		charCat(&x);	//	pop한 값을 postfixExp에 입력한다.
	}

}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
	int opr1, opr2, i;

	int length = strlen(postfixExp);	// length는 입력받는 postfixExp의 크기 만큼 값을 입력 받는다.
	char symbol;
	evalStackTop = -1;

	for (i = 0; i < length; i++)	// postfixExp의  크기 만큼 반복
	{
		symbol = postfixExp[i];	// postfixExp 의 원소 하나를 symbol에 복사한다.
		if (getToken(symbol) == operand) {	// 복사한 symbol이 피연산자이면
			evalPush(symbol - '0');	// 문자-48을 해줌으로써 정수형으로 인자를 보낸다.
		}
		else {	//복사한 symbol이 피연산자가 아니라면
			opr2 = evalPop();	// evalStack의 Top에 위치한 원소 하나를 Pop시킨다. (스택삭제)
			opr1 = evalPop();	// evalStack의 Top에 위치한 다음 원소 하나를 Pop시킨다. (스택삭제)
			switch (getToken(symbol)) {	//symbol이 피연산자가 아니기 때문에 연산자 이므로 어떤 연산자인지 판별
			case plus: evalPush(opr1 + opr2); break;	//plus일 경우 pop시킨 두 원소를 더함. 더한 값을 evalStack에 입력
			case minus: evalPush(opr1 - opr2); break;	//minus일 경우 pop시킨 두 원소를 뺌. 뺀 값을 evalStack에 입력
			case times: evalPush(opr1 * opr2); break;	//times일 경우 pop시킨 두 원소를 곱함. 곱한 값을 evalStack에 입력
			case divide: evalPush(opr1 / opr2); break;	//divide일 경우 pop시킨 두 원소를 나눔. 나눈 값을 evalStack에 입력
			default: break;	// 디폴트 값으로 break
			}
		}
	}
	evalResult = evalPop();	//모든 연산이 끝났으면 결과값을 evalResult에 입력
}

