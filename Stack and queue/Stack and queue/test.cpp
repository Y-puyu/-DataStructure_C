#include <stdio.h>	
#include <iostream>	
#include <stdlib.h>
#include <assert.h>
#define MAX_LEN	(100)
using namespace std;

//typedef int QDataType;
//
//typedef struct SQueue {
//	QDataType data[MAX_LEN];
//	int front;
//	int rear;
//}   _Queue;
//
//// ��ʼ������
//_Queue *_InitQueue(_Queue *q) {
//	_Queue *q = (_Queue*)malloc(sizeof(_Queue));
//	q->front = 0;
//	q->rear = 0;
//	return q;
//}
//
//// ���
//void _QueuePush(_Queue *q, int val) {
//	q->data[q->rear] = val;
//	q->rear++;
//}
//
//// ����
//void _QueuePop(_Queue *q, int val) {
//	int tmp = q->data[q->front];
//	for (int i = 1; i == q->rear; i++) {
//		q->data[i] = q->data[i+1];
//	}
//}







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
	int size;		// ��ʾ���������ݸ���
}	Queue;

// ��ʼ��/����
void QueueInit(Queue *queue) {
	queue->front = queue->rear = NULL;
	queue->size = 0;
}

// ���
void QueuePush(Queue *queue, QDataType val) {
	// ������
	QNode *node = (QNode *)malloc(sizeof(QNode));
	assert(node);
	node->val = val;
	node->next = NULL;
	queue->size++;
	
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
	assert(queue->size > 0);
	queue->size--;

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
	for (QNode *q = qtmp->front; q != NULL; q=q->next) {
		cout << qtmp->front->val << ' ';
		qtmp->front = qtmp->front->next;
	}
	cout << endl;
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
	cout << "**************************************" << endl;
}

int main() {
	char x;
	Stack stack;
	Queue queue;
	menu();
	while (cin >> x) {
		switch (x) {
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
		case 'e':

			break;

		case 'f':
			break;

		case 'g':
			break;
		case 'h':
			break;
		case 'i':
			break;

		case 'j':
			break;

		case 'k':
			break;
		case 'l':
			break;
		

		// ��ʽ����
		case 'm':
			cout << "��ʼ������" << endl;
			QueueInit(&queue);
			cout << "���г�ʼ���ɹ�" << endl;
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
			cout << "��ӡ����Ԫ��" << endl;
			QueuePrint(&queue);
			menu();
			break;
		}
	}
	system("pause");
	return 0;
}