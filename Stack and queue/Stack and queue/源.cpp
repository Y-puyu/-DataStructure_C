//#include <stdio.h>	
//#include <iostream>	
//#include <stdlib.h>
//#include <assert.h>
//#define MAX_LEN	(100)
//using namespace std;
//
//typedef int QDataType;
//
//typedef struct SQueue {
//	QDataType data[MAX_LEN];
//	int front;
//	int rear;
//}   _Queue;
//
//// ��ʼ������
//_Queue *_InitQueue(_Queue *queue) {
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
//void _QueuePop(_Queue *q) {
//	int tmp = q->data[q->front];
//	for (int i = 1; i == q->rear; i++) {
//		q->data[i] = q->data[i + 1];
//	}
//}
//
//
//int main() {
//	_Queue q;
//	_InitQueue(&q);
//	_QueuePush(&q, 1);
//	_QueuePush(&q, 2);
//	_QueuePop(&q);
//	return 0;
//
//}