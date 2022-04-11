/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;

	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
	if (cQ == NULL) return 1;
	free(cQ);
	return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)	// ť�� ����ִ��� Ȯ���ϴ� �Լ�, ť�� ��������� �����޼����� ����ϰ� ���̸� True �� ���� 1�� �����Ѵ�. �����̸� False�ǰ��� 0 ����.
{
	if (cQ->front == cQ->rear) {	// rear�� ��ġ�� front�� ������� ť�� ���Ұ� �ϳ��� �����Ƿ� ť�� ����ִ�.
		printf("���� ť�� ����ֽ��ϴ�.\n");	//�����޼��� ���
		return 1;	//True�� ���� 1 ����
	}
	return 0;	//False�� ���� 0 ����
}

/* complete the function */
int isFull(QueueType *cQ)	// ť�� ���� ä���� �ִ��� Ȯ���ϴ� �Լ�, ť�� ���� �������� �����޼����� ����ϰ� ���̸� True�� ���� 1�� �����Ѵ�. �����̸� False�ǰ��� 0 ����.
{
	if (cQ->rear == (MAX_QUEUE_SIZE - 1)) {	// rear�� ��ġ�� ť�� ������-1�� ��� ť�� ���� ���ִ� �����̴�. MAX_QUEUE_SIZE - 1�� ������ ť�� ������ ���Ҹ� ����Ű�� ����
		printf("���� ť�� ���� ���ֽ��ϴ�.\n");	//�����޼��� ���
		return 1;	//True�� ���� 1 ����
	}
	return 0;	//False�� ���� 0 ����
}


/* complete the function */
void enQueue(QueueType *cQ, element item)	//ť�� �Է��ϴ� �Լ�, ť�� �����Ϳ� �Է��� item�� ���ڷ� �޾� ť�� �Է½�Ų��.
{
	
	if (isFull(cQ)) return;	//ť�� ���� ���ִ��� ����
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;	// rear�� ��ĭ �̵���Ų��. ����ť�̱� ������ SIZE���� ũ�� �ٽ� ó������ ���Ұ� ���ԵǾ�� �ϹǷ� ������ ������ �Ѵ�.
		cQ->queue[cQ->rear] = item;	// item�� rear�� ����Ű�� �ڸ��� �Է���
	}
	return 0;
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)	//ť�� ����� �Լ�, ť�� �����Ϳ� ���� item�� �����͸� �޾� ť�� �����. ť�� ���Լ����� �����̱� ������ front �� �����.
{
	if (isEmpty(cQ))	//ť�� ����ִ��� Ȯ��
		return;
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;	// front�� ��ĭ ������Ų��. ����ť�̱� ������ SIZE���� ũ�� �ٽ� ó������ ���ư��� �ϹǷ� ������ ������ �Ѵ�.
		*item = cQ->queue[cQ->front];	// ��ĭ ������Ų �ڸ��� �ִ� ���Ҹ� �����ϰ� front�� ������ ť�� ���Ҹ� �����.
	}
	return 0;
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while (i != last) {
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}
