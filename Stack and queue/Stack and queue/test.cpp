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

// 初始化队列
void InitSQueue(SQueue *q) {
	q->front = q->rear = -1;
}

// 入队
void SQueuePush(SQueue *q, int val) {
	q->rear++;
	q->data[q->rear] = val;
}

// 出队
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
// 用单链表实现队列
// 链表的结点
typedef struct QNode {
	QDataType val;
	struct QNode *next;
}	QNode;

// 队列
typedef struct Queue {
	QNode *front;	// 指向链表的第一个结点，如果链表为空， == NULL
	QNode *rear;	// 指向链表的最后一个结点，如果链表为空， == NULL
}	Queue;

// 初始化/销毁
void QueueInit(Queue *queue) {
	queue->front = queue->rear = NULL;
}

// 入队
void QueuePush(Queue *queue, QDataType val) {
	// 申请结点
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

// 出队
void QueuePop(Queue *queue) {
	assert(queue != NULL);
	QNode *old_front = queue->front;
	queue->front = queue->front->next;
	free(old_front);

	if (queue->front == NULL) {
		queue->rear = NULL;
	}
}

// 打印队列元素        
void QueuePrint(Queue *queue) {
	Queue *qtmp = queue;
	for (QNode *q = qtmp->front; q != NULL; q=q->next) {
		cout << q->val << "  ";
		// qtmp->front = qtmp->front->next;   鬼知道我在干什么...出了bug 郁闷了1天....
	}
	cout << endl;
}

// 数据类型
typedef int SDataType;

// 利用静态顺序表实现栈
typedef struct {
	SDataType	array[MAX_LEN];
	int			top;	// 职责就是原来的 size
}	Stack;

// 初始化栈
void StackInit(Stack *stack) {
	stack->top = 0;
}

// 入栈 只能从栈顶插入
void StackPush(Stack *stack, SDataType val) {
	assert(stack);
	assert(stack->top < MAX_LEN);

	stack->array[stack->top] = val;
	stack->top++;
}

// 出栈 只能从栈顶删除
void StackPop(Stack *stack) {
	assert(stack);
	assert(stack->top > 0);

	stack->top--;
}

// 打印栈元素
void StackPrint(Stack *stack) {
	assert(stack);
	for (int i = 0; i < stack->top; i++) {
		cout << stack->array[i] << "  ";
	}
	cout << endl;
}

// 用单链表模拟实现链式栈
typedef int SLDataType;

typedef struct SListNode {
	SLDataType	data;
	struct SListNode *next;
}	SListNode;

typedef struct SList {
	struct SListNode *first;
}	SList;

// 初始化单链表
void SListInit(SList *list) {
	assert(list != NULL);
	list->first = NULL;
}

// 申请单链表节点空间
SListNode * BuySListNode(SLDataType data) {
	SListNode *node = (SListNode *)malloc(sizeof(SListNode));
	assert(node != NULL);
	node->data = data;
	node->next = NULL;
	return node;
}

// 单链表尾插即栈元素入栈
void SListPushFront(SList *list, SLDataType data) {
	assert(list != NULL);

	// 1. Node 空间
	SListNode *node = BuySListNode(data);
	// 2. 新的第一个结点的下一个结点就是原来的第一个结点
	node->next = list->first;
	// 3. 记录新的第一个结点
	list->first = node;
}

void SListPopFront(SList *list) {
	assert(list);	// 没有链表
	assert(list->first != NULL);	// 有链表，但是链表是空的

	SListNode *old_first = list->first;
	list->first = list->first->next;
	free(old_first);
}

void SListPushBack(SList *list, SLDataType data) {
	assert(list != NULL);

	if (list->first == NULL) {
		// 链表为空
		SListPushFront(list, data);
		return;
	}

	// 链表中已经有结点的情况
	// 找最后一个结点
	SListNode *lastone = list->first;
	for (; lastone->next != NULL; lastone = lastone->next) {
	}
	// lastone 就是最后一个结点

	// 申请空间
	SListNode *node = BuySListNode(data);
	lastone->next = node;
}

// 单链表尾删即栈元素出栈
void SListPopBack(SList *list) {
	assert(list != NULL);
	assert(list->first != NULL);	// 0 个

	if (list->first->next == NULL) {
		// 1 个
		SListPopFront(list);
		return;
	}

	// 通常情况 >= 2 个
	SListNode *cur;
	for (cur = list->first; cur->next->next != NULL; cur = cur->next) {
	}
	// cur 就是倒数第二个结点
	free(cur->next);
	cur->next = NULL;
}
void SListPrint(SList *list) {
	for (SListNode *cur = list->first; cur != NULL; cur = cur->next) {
		cout << cur->data << " ";
	}
	cout << endl;
}

// 菜单
void menu() {
	cout << "********************************************************************" << endl;
	cout << " 顺序栈:" << endl;
	cout << "	 a. 初始化顺序栈" << endl;
	cout << "	 b. 数据元素val_1入栈，请输入整形数字val_1" << endl;
	cout << "	 c. 栈顶元素出栈" << endl;
	cout << "	 d. 打印顺序栈内元素" << endl;
	cout << endl;
	cout << " 链式栈:" << endl;
	cout << "	 e. 初始化链式栈" << endl;
	cout << "	 f. 数据元素val_2入栈，请输入整形数字val_2" << endl;
	cout << "	 g. 栈顶元素出栈" << endl;
	cout << "	 h. 打印顺序栈内元素" << endl;
	cout << endl;
	cout << " 顺序队列:" << endl;
	cout << "	 i. 初始化顺序队列" << endl;
	cout << "	 j. 数据元素val_3入队，请输入整形数字val_3" << endl;
	cout << "	 k. 队尾元素出队" << endl;
	cout << "	 l. 打印顺序队列元素" << endl;
	cout << endl;
	cout << " 链式队列:" << endl;
	cout << "	 m. 初始化链式队列" << endl;
	cout << "	 n. 数据元素val_4入队，请输入整形数字val_4" << endl;
	cout << "	 o. 队尾元素出队：" << endl;
	cout << "	 p. 打印链式队列元素" << endl;
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
			cout << "初始化顺序栈stack"<< endl;
			StackInit(&stack);
			cout << "初始化成功！" << endl;
			menu();
			break;
		case 'b':
			cout << "数据元素val_1入栈，请输入整形数字val_1:";
			SDataType val_1;
			cin >> val_1;
			StackPush(&stack, val_1);
			cout << "入栈成功" << endl;
			menu();
			break;
		case 'c':
			cout << "栈顶元素出栈：" << endl;
			StackPop(&stack);
			cout << "出栈成功！" << endl;
			menu();
			break;
		case 'd':
			cout << " 打印顺序栈内元素： ";
			StackPrint(&stack);
			menu();
			break;
		
		// 链式栈
		case 'e':
			cout << "初始化链式栈stack" << endl;
			SListInit(&slist);
			cout << "初始化成功！" << endl;
			menu();
			break;
		case 'f':
			cout << "数据元素val_2入栈，请输入整形数字val_2: ";
			SDataType val_2;
			cin >> val_2;
			SListPushBack(&slist, val_2);
			cout << "入栈成功" << endl;
			menu();
			break;
		case 'g':
			cout << "栈顶元素出栈：" << endl;
			SListPopBack(&slist);
			cout << "出栈成功！" << endl;
			menu();
			break;
		case 'h':
			cout << "打印顺序栈内元素： ";
			SListPrint(&slist);
			menu();
			break;

		// 顺序队列
		case 'i':
			cout << "初始化顺序式队列" << endl;
			InitSQueue(&squeue);
			cout << "顺序式队列初始化成功" << endl;
			break;
		case 'j':
			QDataType val_3;
			cout << "数据元素val_3入队，请输入整形数字val:";
			cin >> val_3;
			cout << endl;
			SQueuePush(&squeue, val_3);
			menu();
			break;
		case 'k':
			cout << "队尾元素出队" << endl;
			SQueuePop(&squeue);
			cout << "出队成功" << endl;
			menu();
			break;
		case 'l':
			cout << "打印顺序式队列元素" << endl;
			SQueuePrint(&squeue);
			menu();
			break;
		
		// 链式队列
		case 'm':
			cout << "初始化链式队列" << endl;
			QueueInit(&queue);
			cout << "链式队列初始化成功" << endl;
			menu();
			break;
		case 'n':
			QDataType val_4;
			cout << "数据元素val_4入队，请输入整形数字val:";
			cin >> val_4;
			cout << endl;
			QueuePush(&queue, val_4);
			cout << "入队成功" << endl;
			menu();
			break;
		case 'o':
			cout << "队尾元素出队：" << endl;
			QueuePop(&queue);
			cout << "出队成功" << endl;
			menu();
			break;
		case 'p':
			cout << "打印链式队列元素" << endl;
			QueuePrint(&queue);
			menu();
			break;
		}
	}
	system("pause");
	return 0;
}