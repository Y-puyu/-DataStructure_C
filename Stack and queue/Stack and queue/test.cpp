#include <stdio.h>	
#include <iostream>	
#include <stdlib.h>
#include <assert.h>
#define MAX_LEN	(100)
using namespace std;

typedef int QDataType;

typedef struct {
	QDataType data[MAX_LEN];
	int front;
	int rear;
}   SQueue;

// ��ʼ������
void InitSQueue(SQueue *q) {
	q->front = q->rear = -1;
}

// ���
void SQueuePush(SQueue *q, int val) {
	q->rear++;
	q->data[q->rear] = val;
}

// ����
void SQueuePop(SQueue *q){
	q->front++;
}
void SQueuePrint(SQueue *q) {
	for (int i = 0; i < q->rear; i++) {
		cout << q->data[i] << "  " << endl;
	}

}


typedef int QDataType;
// �õ�����ʵ�ֶ���
// ����Ľ��
typedef struct QNode {
	QDataType val;
	struct QNode *next;
}	QNode;

// ����
typedef struct Queue {
	QNode *front;	// ָ������ĵ�һ����㣬�������Ϊ�գ� == NULL
	QNode *rear;	// ָ����������һ����㣬�������Ϊ�գ� == NULL
}	Queue;

// ��ʼ��/����
void QueueInit(Queue *queue) {
	queue->front = queue->rear = NULL;
}

// ���
void QueuePush(Queue *queue, QDataType val) {
	// ������
	QNode *node = (QNode *)malloc(sizeof(QNode));
	assert(node);
	node->val = val;
	node->next = NULL;
	
	if (queue->rear == NULL) {
		queue->front = queue->rear = node;
	}
	else {
		queue->rear->next = node;
		queue->rear = node;
	}
}

// ����
void QueuePop(Queue *queue) {
	assert(queue != NULL);
	QNode *old_front = queue->front;
	queue->front = queue->front->next;
	free(old_front);

	if (queue->front == NULL) {
		queue->rear = NULL;
	}
}

// ��ӡ����Ԫ��        
void QueuePrint(Queue *queue) {
	Queue *qtmp = queue;
	for (QNode *q = qtmp->front; q != queue->rear; q=q->next) {
		cout << qtmp->front->val << ' ';
		// qtmp->front = qtmp->front->next;   ����bug ����1��....
	}
	cout << queue->rear->val<<endl;
}

// ��������
typedef int SDataType;

// ���þ�̬˳���ʵ��ջ
typedef struct {
	SDataType	array[MAX_LEN];
	int			top;	// ְ�����ԭ���� size
}	Stack;

// ��ʼ��ջ
void StackInit(Stack *stack) {
	stack->top = 0;
}

// ��ջ ֻ�ܴ�ջ������
void StackPush(Stack *stack, SDataType val) {
	assert(stack);
	assert(stack->top < MAX_LEN);

	stack->array[stack->top] = val;
	stack->top++;
}

// ��ջ ֻ�ܴ�ջ��ɾ��
void StackPop(Stack *stack) {
	assert(stack);
	assert(stack->top > 0);

	stack->top--;
}

// ��ӡջԪ��
void StackPrint(Stack *stack) {
	assert(stack);
	for (int i = 0; i < stack->top; i++) {
		cout << stack->array[i] << "  ";
	}
	cout << endl;
}

// �˵�
void menu() {
	cout << "**************************************" << endl;
	cout << "a. ��ʼ��ջ" << endl;
	cout << "b. ��ջ" << endl;
	cout << "c. ��ջ" << endl;
	cout << "d. ��ӡջ��Ԫ��" << endl;
	cout << "e. " << endl;
	cout << "f. " << endl;
	cout << "g. " << endl;
	cout << "h. " << endl;
	cout << "i. " << endl;
	cout << "g. " << endl;
	cout << "h. " << endl;
	cout << "k. " << endl;
	cout << "m. ��ʼ����ʽ����" << endl;
	cout << "n. ����Ԫ��val_4��ӣ���������������val:" << endl;
	cout << "o. ��βԪ�س��ӣ�" << endl;
	cout << "p. ��ӡ��ʽ����Ԫ��" << endl;
	cout << "**************************************" << endl;
}

int main() {
	char x;
	Stack stack;
	Queue queue;
	SQueue squeue;
	menu();
	while (cin >> x) {
		switch (x) {
		// ˳��ʽջ
		case 'a':
			cout << "��ʼ��ջstack,��ʼ���ɹ���"<< endl;
			StackInit(&stack);
			menu();
			break;
		case 'b':
			cout << "����Ԫ��val_1��ջ����������������val_1:";
			SDataType val_1;
			cin >> val_1;
			StackPush(&stack, val_1);
			cout << "��ջ�ɹ�" << endl;
			menu();
			break;
		case 'c':
			cout << "ջ��Ԫ�س�ջ��" << endl;
			StackPop(&stack);
			cout << "��ջ�ɹ���" << endl;
			menu();
			break;
		case 'd':
			cout << " ��ӡջ��Ԫ�أ� ";
			StackPrint(&stack);
			menu();
			break;
		
		// ��ʽջ
		case 'e':

			break;

		case 'f':
			break;

		case 'g':
			break;
		case 'h':
			break;

		// ˳�����
		case 'i':
			cout << "��ʼ��˳��ʽ����" << endl;
			InitSQueue(&squeue);
			cout << "˳��ʽ���г�ʼ���ɹ�" << endl;
			break;

		case 'j':
			QDataType val_3;
			cout << "����Ԫ��val_3��ӣ���������������val:";
			cin >> val_3;
			cout << endl;
			SQueuePush(&squeue, val_3);
			menu();
			break;

		case 'k':
			cout << "��βԪ�س���" << endl;
			SQueuePop(&squeue);
			cout << "���ӳɹ�" << endl;
			menu();
			break;
		case 'l':
			cout << "��ӡ˳��ʽ����Ԫ��" << endl;
			SQueuePrint(&squeue);
			menu();
			break;
		

		// ��ʽ����
		case 'm':
			cout << "��ʼ����ʽ����" << endl;
			QueueInit(&queue);
			cout << "��ʽ���г�ʼ���ɹ�" << endl;
			menu();
			break;

		case 'n':
			QDataType val_4;
			cout << "����Ԫ��val_4��ӣ���������������val:";
			cin >> val_4;
			cout << endl;
			QueuePush(&queue, val_4);
			menu();
			break;


		case 'o':
			cout << "��βԪ�س��ӣ�" << endl;
			QueuePop(&queue);
			cout << "���ӳɹ�" << endl;
			menu();
			break;
		case 'p':
			cout << "��ӡ��ʽ����Ԫ��" << endl;
			QueuePrint(&queue);
			menu();
			break;
		}
	}
	system("pause");
	return 0;
}