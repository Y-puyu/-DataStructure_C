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
//// 初始化队列
//_Queue *_InitQueue(_Queue *q) {
//	_Queue *q = (_Queue*)malloc(sizeof(_Queue));
//	q->front = 0;
//	q->rear = 0;
//	return q;
//}
//
//// 入队
//void _QueuePush(_Queue *q, int val) {
//	q->data[q->rear] = val;
//	q->rear++;
//}
//
//// 出队
//void _QueuePop(_Queue *q, int val) {
//	int tmp = q->data[q->front];
//	for (int i = 1; i == q->rear; i++) {
//		q->data[i] = q->data[i+1];
//	}
//}







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
	int size;		// 表示队列中数据个数
}	Queue;

// 初始化/销毁
void QueueInit(Queue *queue) {
	queue->front = queue->rear = NULL;
	queue->size = 0;
}

// 入队
void QueuePush(Queue *queue, QDataType val) {
	// 申请结点
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

// 出队
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
}

int main() {
	char x;
	Stack stack;
	while (cin >> x) {
		switch (x) {
		case 'a':
			cout << "初始化栈stack,初始化成功！"<< endl;
			StackInit(&stack);
			break;
		case 'b':
			cout << "数据元素val入栈，请输入整形数字val:" << endl;
			SDataType val;
			cin >> val;
			StackPush(&stack, val);
			cout << "入栈成功" << endl;
			break;
		case 'c':
			cout << "栈顶元素出栈：" << endl;
			StackPop(&stack);
			cout << "出栈成功！" << endl;
			StackPrint(&stack);
			break;
		}
	}


	system("pause");
	return 0;
}