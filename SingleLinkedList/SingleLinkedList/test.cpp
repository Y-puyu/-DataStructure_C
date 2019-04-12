#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <iostream>
using namespace std;

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

// ������ͷ��
void SListPushFront(SList *list, SLDataType data) {
	assert(list != NULL);
	SListNode *node = BuySListNode(data);
	node->next = list->first;
	list->first = node;
}

// ������ͷɾ
void SListPopFront(SList *list) {
	assert(list);	// û������
	assert(list->first != NULL);	// ���������������ǿյ�
	SListNode *old_first = list->first;
	list->first = list->first->next;
	free(old_first);
}

// ɾ��ֵΪdata�Ľڵ�
void SListRemove(SList *list) {
	printf("������Ҫɾ��������Ԫ�أ� ");
	SLDataType data;
	cin >> data;
	SListNode *prev = NULL;
	SListNode *cur = list->first;
	while (cur != NULL && cur->data != data) {
		prev = cur;
		cur = cur->next;
	}
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

// ������ӡ������
void SListPrint(SList *list) {
	for (SListNode *cur = list->first; cur != NULL; cur = cur->next) {
		printf("%d --> ", cur->data);
	}
	printf("NULL\n");
}

// ��Ϊ�ǵݼ���������
void SListSort(SList *list) {  
	SListNode *cur, *prev;
	int tmp;
	for (cur = list->first; cur != NULL; cur = cur->next) {
		for (prev = cur->next; prev != NULL; prev = prev->next) {
			if (prev->data > cur->data) {   // �ǵݼ�����
				tmp = cur->data;
				cur->data = prev->data;
				prev->data = tmp;
			}
		}
	}
}

// �ڷǵݼ����������в���һ��Ԫ��ʹ������Ȼ����
void SListInsertAfter(SList *list) {
	SListNode *prev;
	SLDataType data;
	printf("���������֣� ");
	cin >> data;
	SListPushFront(list, data);
	SListSort(list);
}

// ���õ�����
void ReverseList(SList* list) {
	SListNode *newHead = NULL;
	SListNode *node;

	while (list-> first!= NULL) {
		node = list->first;
		list->first = list->first->next;
		node->next = newHead;
		newHead = node;
	}
	list->first = newHead;
}

// ���������ǵݼ����������ϲ�Ϊһ���ǵݼ���������
void SListMerge(SList* Alist, SList* Blist) {
	int flag = 1;
	SListNode *cur = Blist->first;
	printf("�����ͷ�巨����������A��\n");
	do {
		int num;
		char p;
		printf("���������֣� ");
		scanf("%d", &num);
		SListPushFront(Alist, num);
		SListPrint(Alist);
		printf("�Ƿ��������ͷ�巨����y/n)�� ");
		cin >> p;
		if (p != 'y') flag = 0;
	} while (flag);
	printf("��������A����Ϊ�ǵݼ��������У� ");
	SListSort(Alist);
	SListPrint(Alist);
	printf("�����ͷ�巨����������B��\n");
	flag = 1;         // �м�����flag...
	do {
		int num;
		char c;
		printf("���������֣� ");
		scanf("%d", &num);
		SListPushFront(Blist, num);
		SListPrint(Blist);
		printf("�Ƿ��������ͷ�巨����y/n)�� ");
		cin >> c;
		if (c != 'y') flag = 0;
	} while (flag);
	printf("��������B����Ϊ�ǵݼ��������У� ");
	SListSort(Blist);
	SListPrint(Blist);
	printf("��������A��������B�ϲ�Ϊ�ǵݼ���������");

	SListNode *node = Alist->first;
	while (Alist->first != NULL) {
		// ��֮ǰ��������ͷɾ
		node = Alist->first;
		Alist->first = Alist->first->next;

		// ����������ͷ��
		node->next = Blist->first;
		Blist->first = node;
	}
	Blist->first = node;
	SListSort(Blist);
	SListPrint(Blist);
}
// �˵�����
void menu() {
	printf("************************************************************\n");
	printf("*  1��ͷ�巨����������	\n");
	printf("*  2��������ӡ������\n");
	printf("*  3�����õ�����\n");
	printf("*  4����Ϊ�ǵݼ���������\n");
	printf("*  5���ڷǵݼ����������в���һ��Ԫ��ʹ������Ȼ����\n");
	printf("*  6���ڷǵݼ�����������ɾ��ֵΪx�Ľ��\n");
	printf("*  7�����������ǵݼ����������ϲ�Ϊһ���ǵݼ���������\n");
	printf("************************************************************\n");
	printf("��ѡ��:");
}

int main() {
	SList list;
	SList Alist;
	SList Blist;
	SListInit(&list);
	SListInit(&Alist);
	SListInit(&Blist);
	int n;
	char c = 'y';
	int flag = 1;
	menu();
	do {
		scanf("%d", &n);
		switch (n) {
		case 1:
			// ͷ�巨����������
			do {
				int num;
				char p;
				printf("���������֣� ");
				scanf("%d", &num);
				SListPushFront(&list, num);
				SListPrint(&list);
				printf("�Ƿ��������ͷ�巨����y/n)�� ");
				cin >> p;
				if (p != 'y') flag = 0;
			} while (flag);
			menu();
			break;
		case 2:
			// ������ӡ������
			SListPrint(&list);
			menu();
			break;
		case 3:
			// ���õ�����
			ReverseList(&list);
			SListPrint(&list);
			menu();
			break;
		case 4:
			// ��Ϊ�ǵݼ���������
			SListSort(&list);
			SListPrint(&list);
			menu();
			break;
		case 5:
			// �ڷǵݼ����������в���һ��Ԫ��ʹ������Ȼ����
			SListInsertAfter(&list);
			SListPrint(&list);
			menu();
			break;

		case 6:
			// �ڷǵݼ�����������ɾ��ֵΪx�Ľ��
			SListPrint(&list);
			SListRemove(&list);
			SListPrint(&list);
			menu();
			break;
		case 7:
			SListMerge(&Alist, &Blist);
			menu();
			break;
		}
	} while (1);

	system("pause");
	return 0;
}