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
	int i = q->rear + 1;
	for (int j= 0; j < i; j++) {
		q->data[j] = q->data[j+1];
	}
	q->rear--;
}
void SQueuePrint(SQueue *q) {
	for (int i = q->front+1; i < q->rear+1; i++) {
		cout << q->data[i] << " " ;
	}
	cout << endl;
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
	for (QNode *q = qtmp->front; q != NULL; q=q->next) {
		cout << q->val << "  ";
		// qtmp->front = qtmp->front->next;   ��֪�����ڸ�ʲô...����bug ������1��....
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

// �õ�����ģ��ʵ����ʽջ
typedef int SLDataType;

typedef struct SListNode {
	SLDataType	data;
	struct SListNode *next;
}	SListNode;

typedef struct SList {
	struct SListNode *first;
}	SList;

// ��ʼ��������
void SListInit(SList *list) {
	assert(list != NULL);
	list->first = NULL;
}

// ���뵥����ڵ�ռ�
SListNode * BuySListNode(SLDataType data) {
	SListNode *node = (SListNode *)malloc(sizeof(SListNode));
	assert(node != NULL);
	node->data = data;
	node->next = NULL;
	return node;
}

// ������β�弴ջԪ����ջ
void SListPushFront(SList *list, SLDataType data) {
	assert(list != NULL);

	// 1. Node �ռ�
	SListNode *node = BuySListNode(data);
	// 2. �µĵ�һ��������һ��������ԭ���ĵ�һ�����
	node->next = list->first;
	// 3. ��¼�µĵ�һ�����
	list->first = node;
}

void SListPopFront(SList *list) {
	assert(list);	// û������
	assert(list->first != NULL);	// ���������������ǿյ�

	SListNode *old_first = list->first;
	list->first = list->first->next;
	free(old_first);
}

void SListPushBack(SList *list, SLDataType data) {
	assert(list != NULL);

	if (list->first == NULL) {
		// ����Ϊ��
		SListPushFront(list, data);
		return;
	}

	// �������Ѿ��н������
	// �����һ�����
	SListNode *lastone = list->first;
	for (; lastone->next != NULL; lastone = lastone->next) {
	}
	// lastone �������һ�����

	// ����ռ�
	SListNode *node = BuySListNode(data);
	lastone->next = node;
}

// ������βɾ��ջԪ�س�ջ
void SListPopBack(SList *list) {
	assert(list != NULL);
	assert(list->first != NULL);	// 0 ��

	if (list->first->next == NULL) {
		// 1 ��
		SListPopFront(list);
		return;
	}

	// ͨ����� >= 2 ��
	SListNode *cur;
	for (cur = list->first; cur->next->next != NULL; cur = cur->next) {
	}
	// cur ���ǵ����ڶ������
	free(cur->next);
	cur->next = NULL;
}
void SListPrint(SList *list) {
	for (SListNode *cur = list->first; cur != NULL; cur = cur->next) {
		cout << cur->data << " ";
	}
	cout << endl;
}

// �˵�
void menu() {
	cout << "********************************************************************" << endl;
	cout << " ˳��ջ:" << endl;
	cout << "	 a. ��ʼ��˳��ջ" << endl;
	cout << "	 b. ����Ԫ��val_1��ջ����������������val_1" << endl;
	cout << "	 c. ջ��Ԫ�س�ջ" << endl;
	cout << "	 d. ��ӡ˳��ջ��Ԫ��" << endl;
	cout << endl;
	cout << " ��ʽջ:" << endl;
	cout << "	 e. ��ʼ����ʽջ" << endl;
	cout << "	 f. ����Ԫ��val_2��ջ����������������val_2" << endl;
	cout << "	 g. ջ��Ԫ�س�ջ" << endl;
	cout << "	 h. ��ӡ˳��ջ��Ԫ��" << endl;
	cout << endl;
	cout << " ˳�����:" << endl;
	cout << "	 i. ��ʼ��˳�����" << endl;
	cout << "	 j. ����Ԫ��val_3��ӣ���������������val_3" << endl;
	cout << "	 k. ��βԪ�س���" << endl;
	cout << "	 l. ��ӡ˳�����Ԫ��" << endl;
	cout << endl;
	cout << " ��ʽ����:" << endl;
	cout << "	 m. ��ʼ����ʽ����" << endl;
	cout << "	 n. ����Ԫ��val_4��ӣ���������������val_4" << endl;
	cout << "	 o. ��βԪ�س��ӣ�" << endl;
	cout << "	 p. ��ӡ��ʽ����Ԫ��" << endl;
	cout << "********************************************************************" << endl;
}

int main() {
	char x;
	Stack stack;
	Queue queue;
	SQueue squeue;
	SList slist;
	menu();
	while (cin >> x) {
		switch (x) {
		case 'a':
			cout << "��ʼ��˳��ջstack"<< endl;
			StackInit(&stack);
			cout << "��ʼ���ɹ���" << endl;
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
			cout << " ��ӡ˳��ջ��Ԫ�أ� ";
			StackPrint(&stack);
			menu();
			break;
		
		// ��ʽջ
		case 'e':
			cout << "��ʼ����ʽջstack" << endl;
			SListInit(&slist);
			cout << "��ʼ���ɹ���" << endl;
			menu();
			break;
		case 'f':
			cout << "����Ԫ��val_2��ջ����������������val_2: ";
			SDataType val_2;
			cin >> val_2;
			SListPushBack(&slist, val_2);
			cout << "��ջ�ɹ�" << endl;
			menu();
			break;
		case 'g':
			cout << "ջ��Ԫ�س�ջ��" << endl;
			SListPopBack(&slist);
			cout << "��ջ�ɹ���" << endl;
			menu();
			break;
		case 'h':
			cout << "��ӡ˳��ջ��Ԫ�أ� ";
			SListPrint(&slist);
			menu();
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
			cout << "��ӳɹ�" << endl;
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