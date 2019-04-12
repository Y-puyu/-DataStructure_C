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

// 单链表头插
void SListPushFront(SList *list, SLDataType data) {
	assert(list != NULL);
	SListNode *node = BuySListNode(data);
	node->next = list->first;
	list->first = node;
}

// 单链表头删
void SListPopFront(SList *list) {
	assert(list);	// 没有链表
	assert(list->first != NULL);	// 有链表，但是链表是空的
	SListNode *old_first = list->first;
	list->first = list->first->next;
	free(old_first);
}

// 删除值为data的节点
void SListRemove(SList *list) {
	printf("请输入要删除的数据元素： ");
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

// 遍历打印单链表
void SListPrint(SList *list) {
	for (SListNode *cur = list->first; cur != NULL; cur = cur->next) {
		printf("%d --> ", cur->data);
	}
	printf("NULL\n");
}

// 成为非递减有序单链表
void SListSort(SList *list) {  
	SListNode *cur, *prev;
	int tmp;
	for (cur = list->first; cur != NULL; cur = cur->next) {
		for (prev = cur->next; prev != NULL; prev = prev->next) {
			if (prev->data > cur->data) {   // 非递减有序
				tmp = cur->data;
				cur->data = prev->data;
				prev->data = tmp;
			}
		}
	}
}

// 在非递减有序单链表中插入一个元素使链表仍然有序
void SListInsertAfter(SList *list) {
	SListNode *prev;
	SLDataType data;
	printf("请输入数字： ");
	cin >> data;
	SListPushFront(list, data);
	SListSort(list);
}

// 逆置单链表
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

// 建立两个非递减有序链表并合并为一个非递减有序单链表
void SListMerge(SList* Alist, SList* Blist) {
	int flag = 1;
	SListNode *cur = Blist->first;
	printf("请采用头插法建立单链表A：\n");
	do {
		int num;
		char p;
		printf("请输入数字： ");
		scanf("%d", &num);
		SListPushFront(Alist, num);
		SListPrint(Alist);
		printf("是否继续采用头插法建表（y/n)： ");
		cin >> p;
		if (p != 'y') flag = 0;
	} while (flag);
	printf("将单链表A整理为非递减有序排列： ");
	SListSort(Alist);
	SListPrint(Alist);
	printf("请采用头插法建立单链表B：\n");
	flag = 1;         // 切记重置flag...
	do {
		int num;
		char c;
		printf("请输入数字： ");
		scanf("%d", &num);
		SListPushFront(Blist, num);
		SListPrint(Blist);
		printf("是否继续采用头插法建表（y/n)： ");
		cin >> c;
		if (c != 'y') flag = 0;
	} while (flag);
	printf("将单链表B整理为非递减有序排列： ");
	SListSort(Blist);
	SListPrint(Blist);
	printf("将单链表A、单链表B合并为非递减有序单链表：");

	SListNode *node = Alist->first;
	while (Alist->first != NULL) {
		// 对之前的链表做头删
		node = Alist->first;
		Alist->first = Alist->first->next;

		// 对新链表做头插
		node->next = Blist->first;
		Blist->first = node;
	}
	Blist->first = node;
	SListSort(Blist);
	SListPrint(Blist);
}
// 菜单函数
void menu() {
	printf("************************************************************\n");
	printf("*  1：头插法建立单链表	\n");
	printf("*  2：遍历打印单链表\n");
	printf("*  3：逆置单链表\n");
	printf("*  4：成为非递减有序单链表\n");
	printf("*  5：在非递减有序单链表中插入一个元素使链表仍然有序\n");
	printf("*  6：在非递减有序链表中删除值为x的结点\n");
	printf("*  7：建立两个非递减有序链表并合并为一个非递减有序单链表\n");
	printf("************************************************************\n");
	printf("请选择:");
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
			// 头插法建立单链表
			do {
				int num;
				char p;
				printf("请输入数字： ");
				scanf("%d", &num);
				SListPushFront(&list, num);
				SListPrint(&list);
				printf("是否继续采用头插法建表（y/n)： ");
				cin >> p;
				if (p != 'y') flag = 0;
			} while (flag);
			menu();
			break;
		case 2:
			// 遍历打印单链表
			SListPrint(&list);
			menu();
			break;
		case 3:
			// 逆置单链表
			ReverseList(&list);
			SListPrint(&list);
			menu();
			break;
		case 4:
			// 成为非递减有序单链表
			SListSort(&list);
			SListPrint(&list);
			menu();
			break;
		case 5:
			// 在非递减有序单链表中插入一个元素使链表仍然有序
			SListInsertAfter(&list);
			SListPrint(&list);
			menu();
			break;

		case 6:
			// 在非递减有序链表中删除值为x的结点
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