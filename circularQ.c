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
int isEmpty(QueueType *cQ)	// 큐가 비어있는지 확인하는 함수, 큐가 비어있으면 에러메세지를 출력하고 참이면 True 의 값인 1을 리턴한다. 거짓이면 False의값인 0 리턴.
{
	if (cQ->front == cQ->rear) {	// rear의 위치가 front와 같을경우 큐에 원소가 하나도 없으므로 큐가 비어있다.
		printf("원형 큐가 비어있습니다.\n");	//에러메세지 출력
		return 1;	//True의 값인 1 리턴
	}
	return 0;	//False의 값인 0 리턴
}

/* complete the function */
int isFull(QueueType *cQ)	// 큐가 가득 채워져 있는지 확인하는 함수, 큐가 가득 차있으면 에러메세지를 출력하고 참이면 True의 값인 1을 리턴한다. 거짓이면 False의값인 0 리턴.
{
	if (cQ->rear == (MAX_QUEUE_SIZE - 1)) {	// rear의 위치가 큐의 사이즈-1일 경우 큐가 가득 차있는 상태이다. MAX_QUEUE_SIZE - 1인 이유는 큐의 마지막 원소를 가리키기 때문
		printf("원형 큐가 가득 차있습니다.\n");	//에러메세지 출력
		return 1;	//True의 값인 1 리턴
	}
	return 0;	//False의 값인 0 리턴
}


/* complete the function */
void enQueue(QueueType *cQ, element item)	//큐를 입력하는 함수, 큐의 포인터와 입력할 item을 인자로 받아 큐에 입력시킨다.
{
	
	if (isFull(cQ)) return;	//큐가 가득 차있는지 점검
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;	// rear를 한칸 이동시킨다. 원형큐이기 때문에 SIZE보다 크면 다시 처음부터 원소가 삽입되어야 하므로 나머지 연산을 한다.
		cQ->queue[cQ->rear] = item;	// item을 rear가 가리키는 자리로 입력함
	}
	return 0;
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)	//큐를 지우는 함수, 큐의 포인터와 지울 item의 포인터를 받아 큐를 지운다. 큐는 선입선출의 구조이기 때문에 front 를 지운다.
{
	if (isEmpty(cQ))	//큐가 비어있는지 확인
		return;
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;	// front를 한칸 증가시킨다. 원형큐이기 때문에 SIZE보다 크면 다시 처음으로 돌아가야 하므로 나머지 연산을 한다.
		*item = cQ->queue[cQ->front];	// 한칸 증가시킨 자리에 있는 원소를 제거하고 front로 가리켜 큐의 원소를 지운다.
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
