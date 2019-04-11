#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef int SLDataType;

typedef struct SListNode {
	SLDataType	data;
	struct SListNode *next;
}	SListNode;

typedef struct SList {
	struct SListNode *first;
}	SList;

void SListInit(SList *list)
{
	assert(list != NULL);
	list->first = NULL;
}


void SListDestroy(SList *list)
{
	SListNode *next;
	for (SListNode *cur = list->first; cur != NULL; cur = next) {
		next = cur->next;
		free(cur);
	}

	list->first = NULL;
}

SListNode * BuySListNode(SLDataType data)
{
	SListNode *node = (SListNode *)malloc(sizeof(SListNode));
	assert(node != NULL);
	node->data = data;
	node->next = NULL;

	return node;
}

void SListPushFront(SList *list, SLDataType data)
{
	assert(list != NULL);

	// 1. Node 空间
	SListNode *node = BuySListNode(data);
	// 2. 新的第一个结点的下一个结点就是原来的第一个结点
	node->next = list->first;
	// 3. 记录新的第一个结点
	list->first = node;
}

void SListPopFront(SList *list)
{
	assert(list);	// 没有链表
	assert(list->first != NULL);	// 有链表，但是链表是空的

	SListNode *old_first = list->first;
	list->first = list->first->next;
	free(old_first);
}

void SListPushBack(SList *list, SLDataType data)
{
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

void SListPopBack(SList *list)
{
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

SListNode * SListFind(SList *list, SLDataType data)
{
	for (SListNode *cur = list->first; cur != NULL; cur = cur->next) {
		if (cur->data == data) {
			return cur;
		}
	}

	// 没找到
	return NULL;
}

void SListInsertAfter(SListNode *pos, SLDataType data)
{
	SListNode *node = BuySListNode(data);
	node->next = pos->next;
	pos->next = node;
}

void SListEraseAfter(SListNode *pos)
{
	SListNode *next = pos->next->next;	// next 是 D
	free(pos->next);
	pos->next = next;
}

void SListRemove(SList *list, SLDataType data)
{
	// 重点是找到 data 这个结点的前一个结点
	// previous	prev

	SListNode *prev = NULL;
	SListNode *cur = list->first;

	while (cur != NULL && cur->data != data) {
		prev = cur;
		cur = cur->next;
	}

	// cur == NULL 表示没找到
	// cur != NULL && prev != NULL
	// cur 就是要删的结点，同时 prev 就是要删的前一个结点
	// cur != NULL && prev == NULL 头删
	if (cur == NULL) {
		return;
	}

	if (prev == NULL) {
		SListPopFront(list);
		return;
	}

	prev->next = cur->next;
	free(cur);
}

void SListPrint(SList *list)
{
	for (SListNode *cur = list->first; cur != NULL; cur = cur->next) {
		printf("%d --> ", cur->data);
	}
	printf("NULL\n");
}


void TestSList1()
{
	SList list;
	SListInit(&list);

	SListPrint(&list);

	SListPushFront(&list, 3);
	SListPushFront(&list, 2);
	SListPushFront(&list, 1);
	SListPrint(&list);

	SListPopFront(&list);
	SListPopFront(&list);

	SListPrint(&list);

	SListPopFront(&list);
	SListPrint(&list);

	SListPushBack(&list, 4);
	SListPushBack(&list, 5);
	SListPushBack(&list, 6);
	SListPrint(&list);

	SListPopBack(&list);
	SListPrint(&list);
	SListPopBack(&list);
	SListPrint(&list);
	SListPopBack(&list);
	SListPrint(&list);
}

void TestSList2() {

	SList list;
	SListInit(&list);

	SListPushBack(&list, 1);
	SListPushBack(&list, 2);
	SListPushBack(&list, 3);
	SListPushBack(&list, 4);
	SListPushBack(&list, 5);
	SListPrint(&list);

	// 3 后面插入 10
	SListNode *n3 = SListFind(&list, 3);
	SListInsertAfter(n3, 10);
	SListPrint(&list);

	SListEraseAfter(n3);
	SListPrint(&list);
}

void TestSList3()
{
	SList list;
	SListInit(&list);

	SListPushBack(&list, 1);
	SListPushBack(&list, 2);
	SListPushBack(&list, 3);
	SListPushBack(&list, 4);
	SListPushBack(&list, 5);
	SListPrint(&list);


	SListRemove(&list, 3);
	SListPrint(&list);

	SListRemove(&list, 1);
	SListPrint(&list);

	SListRemove(&list, 5);
	SListPrint(&list);
}

int main() {
	TestSList3();
	system("pause");
	return 0;
}