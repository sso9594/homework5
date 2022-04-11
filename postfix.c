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

 /* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum {
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	/* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		/* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack�� top */

int evalResult = 0;	   /* ��� ����� ���� */

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
	printf("\t2019038073  �Ž¿�\n");
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
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
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
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while (*exp != '\0')
	{
		/* �ʿ��� ���� �ϼ� */
		if (getPriority(*exp) == operand)	// �Է¹��� exp�� getPriority()�Լ��� �־� ���ϰ����� operand�� ������ exp�� �ǿ����� �� ����̴�.
		{
			x = *exp;	// exp�� ����Ű�� �ִ� ���� ���� x�� ����
			charCat(&x);	// charCat() �Լ��� �̿��Ͽ� postfixExp�� �߰��Ѵ�.
		}
		else if (getPriority(*exp) == lparen) {	// �Է¹��� exp�� getPriority()�Լ��� �־� ���ϰ����� lparen�� ������ exp�� ���� ��ȣ �� ����̴�.

			postfixPush(*exp);	// ���ʰ�ȣ ���ڸ� postfixPush() �Լ��� �̿��Ͽ� postfixStack�� Top�� �Է��Ѵ�.
		}
		else if (getPriority(*exp) == rparen)	// �Է¹��� exp�� getPriority()�Լ��� �־� ���ϰ����� rparen�� ������ exp�� ������ ��ȣ�� ����̴�.
		{
			while ((x = postfixPop()) != '(') {	// ���ʰ�ȣ�� ���� �� ���� �ݺ��Ѵ�.
				charCat(&x);	// charCat() �Լ��� �̿��Ͽ� ���� ��ȣ�� ���� �� ���� postfixStack�� pop ���� postfixExp�� �Է��Ѵ�.
			}
		}
		else // getPriority(*exp)�� ��Ģ���� ��ȣ �� ���
		{
			while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))	// postfixStack[postfixStackTop]�� �켱������ *exp�� �켱�������� Ŭ�� ���� �ݺ�. �����ڸ��� �켱������ �ֱ� ������ ���ÿ� �ִ� �����ڿ� *exp�� �����ڸ� ���Ѵ�.
			{
				x = postfixPop();	// postfixStack�� �ִ� �����ڰ� �켱������ Ŭ���
				charCat(&x);	// postfixStack���� pop�� ��Ų��.
			}
			postfixPush(*exp);	// ������ ���ڸ� postfixPush() �Լ��� �̿��Ͽ� postfixStack�� Top�� �Է��Ѵ�.
		}
		exp++;

	}

	/* �ʿ��� ���� �ϼ� */
	while (postfixStackTop != -1)	// postfixStackTop�� -1�� �ƴҰ�� �ݺ�, �Է� ���� �켱������� ������� �ԷµǾ�����. postfixStack�� �ִ� ������ ����ǥ������� postfixExp�� �Է��ϱ� ���� �ݺ���
	{
		x = postfixPop();	// postfixStack�� �ִ� ���� pop �Ѵ�.
		charCat(&x);	//	pop�� ���� postfixExp�� �Է��Ѵ�.
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
	/* postfixExp, evalStack�� �̿��� ��� */
	int opr1, opr2, i;

	int length = strlen(postfixExp);	// length�� �Է¹޴� postfixExp�� ũ�� ��ŭ ���� �Է� �޴´�.
	char symbol;
	evalStackTop = -1;

	for (i = 0; i < length; i++)	// postfixExp��  ũ�� ��ŭ �ݺ�
	{
		symbol = postfixExp[i];	// postfixExp �� ���� �ϳ��� symbol�� �����Ѵ�.
		if (getToken(symbol) == operand) {	// ������ symbol�� �ǿ������̸�
			evalPush(symbol - '0');	// ����-48�� �������ν� ���������� ���ڸ� ������.
		}
		else {	//������ symbol�� �ǿ����ڰ� �ƴ϶��
			opr2 = evalPop();	// evalStack�� Top�� ��ġ�� ���� �ϳ��� Pop��Ų��. (���û���)
			opr1 = evalPop();	// evalStack�� Top�� ��ġ�� ���� ���� �ϳ��� Pop��Ų��. (���û���)
			switch (getToken(symbol)) {	//symbol�� �ǿ����ڰ� �ƴϱ� ������ ������ �̹Ƿ� � ���������� �Ǻ�
			case plus: evalPush(opr1 + opr2); break;	//plus�� ��� pop��Ų �� ���Ҹ� ����. ���� ���� evalStack�� �Է�
			case minus: evalPush(opr1 - opr2); break;	//minus�� ��� pop��Ų �� ���Ҹ� ��. �� ���� evalStack�� �Է�
			case times: evalPush(opr1 * opr2); break;	//times�� ��� pop��Ų �� ���Ҹ� ����. ���� ���� evalStack�� �Է�
			case divide: evalPush(opr1 / opr2); break;	//divide�� ��� pop��Ų �� ���Ҹ� ����. ���� ���� evalStack�� �Է�
			default: break;	// ����Ʈ ������ break
			}
		}
	}
	evalResult = evalPop();	//��� ������ �������� ������� evalResult�� �Է�
}

