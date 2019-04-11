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

	// 1. Node �ռ�
	SListNode *node = BuySListNode(data);
	// 2. �µĵ�һ��������һ��������ԭ���ĵ�һ�����
	node->next = list->first;
	// 3. ��¼�µĵ�һ�����
	list->first = node;
}

void SListPopFront(SList *list)
{
	assert(list);	// û������
	assert(list->first != NULL);	// ���������������ǿյ�

	SListNode *old_first = list->first;
	list->first = list->first->next;
	free(old_first);
}

void SListPushBack(SList *list, SLDataType data)
{
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

void SListPopBack(SList *list)
{
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

SListNode * SListFind(SList *list, SLDataType data)
{
	for (SListNode *cur = list->first; cur != NULL; cur = cur->next) {
		if (cur->data == data) {
			return cur;
		}
	}

	// û�ҵ�
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
	SListNode *next = pos->next->next;	// next �� D
	free(pos->next);
	pos->next = next;
}

void SListRemove(SList *list, SLDataType data)
{
	// �ص����ҵ� data �������ǰһ�����
	// previous	prev

	SListNode *prev = NULL;
	SListNode *cur = list->first;

	while (cur != NULL && cur->data != data) {
		prev = cur;
		cur = cur->next;
	}

	// cur == NULL ��ʾû�ҵ�
	// cur != NULL && prev != NULL
	// cur ����Ҫɾ�Ľ�㣬ͬʱ prev ����Ҫɾ��ǰһ�����
	// cur != NULL && prev == NULL ͷɾ
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

	// 3 ������� 10
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