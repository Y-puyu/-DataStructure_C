
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
void SListInit(SList *list)
{
	assert(list != NULL);
	list->first = NULL;
}


// 申请单链表节点空间
SListNode * BuySListNode(SLDataType data)
{
	SListNode *node = (SListNode *)malloc(sizeof(SListNode));
	assert(node != NULL);
	node->data = data;
	node->next = NULL;

	return node;
}

// 单链表头插
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

// 单链表头删
void SListPopFront(SList *list)
{
	assert(list);	// 没有链表
	assert(list->first != NULL);	// 有链表，但是链表是空的

	SListNode *old_first = list->first;
	list->first = list->first->next;
	free(old_first);
}

// 删除值为data的节点
void SListRemove(SList *list)
{
	printf("请输入要删除的数据元素： ");
	// 重点是找到 data 这个结点的前一个结点
	// previous	prev
	SLDataType data;
	cin >> data;
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
void SListInsertAfter(SList *list)
{
	SListNode *prev;
	SLDataType data;
	printf("请输入数字： ");
	cin >> data;
	SListPushFront(list, data);
	SListSort(list);
}

void ReverseList(SList* list) {
	SListNode *newHead = NULL;
	SListNode *node;

	while (list-> first!= NULL) {
		// 对之前的链表做头删
		node = list->first;
		list->first = list->first->next;

		// 对新链表做头插
		node->next = newHead;
		newHead = node;
	}
	list->first = newHead;
}

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













//#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
//
//typedef int SLDataType;
//
//typedef struct SListNode {
//	SLDataType	data;
//	struct SListNode *next;
//}	SListNode;
//
//typedef struct SList {
//	struct SListNode *first;
//}	SList;
//
//// 初始化单链表
//void SListInit(SList *list)
//{
//	assert(list != NULL);
//	list->first = NULL;
//}
//
//// 销毁单链表
//void SListDestroy(SList *list)
//{
//	SListNode *next;
//	for (SListNode *cur = list->first; cur != NULL; cur = next) {
//		next = cur->next;
//		free(cur);
//	}
//
//	list->first = NULL;
//}
//
//// 申请单链表节点空间
//SListNode * BuySListNode(SLDataType data)
//{
//	SListNode *node = (SListNode *)malloc(sizeof(SListNode));
//	assert(node != NULL);
//	node->data = data;
//	node->next = NULL;
//
//	return node;
//}
//
//// 单链表头插
//void SListPushFront(SList *list, SLDataType data)
//{
//	assert(list != NULL);
//
//	// 1. Node 空间
//	SListNode *node = BuySListNode(data);
//	// 2. 新的第一个结点的下一个结点就是原来的第一个结点
//	node->next = list->first;
//	// 3. 记录新的第一个结点
//	list->first = node;
//}
//
//// 单链表头删
//void SListPopFront(SList *list)
//{
//	assert(list);	// 没有链表
//	assert(list->first != NULL);	// 有链表，但是链表是空的
//
//	SListNode *old_first = list->first;
//	list->first = list->first->next;
//	free(old_first);
//}
//
//// 单链表尾插
//void SListPushBack(SList *list, SLDataType data)
//{
//	assert(list != NULL);
//
//	if (list->first == NULL) {
//		// 链表为空
//		SListPushFront(list, data);
//		return;
//	}
//
//	// 链表中已经有结点的情况
//	// 找最后一个结点
//	SListNode *lastone = list->first;
//	for (; lastone->next != NULL; lastone = lastone->next) {
//	}
//	// lastone 就是最后一个结点
//
//	// 申请空间
//	SListNode *node = BuySListNode(data);
//	lastone->next = node;
//}
//
//// 单链表尾删
//void SListPopBack(SList *list)
//{
//	assert(list != NULL);
//	assert(list->first != NULL);	// 0 个
//
//	if (list->first->next == NULL) {
//		// 1 个
//		SListPopFront(list);
//		return;
//	}
//
//	// 通常情况 >= 2 个
//	SListNode *cur;
//	for (cur = list->first; cur->next->next != NULL; cur = cur->next) {
//	}
//	// cur 就是倒数第二个结点
//	free(cur->next);
//	cur->next = NULL;
//}
//
//// 查找单链表元素
//SListNode * SListFind(SList *list, SLDataType data)
//{
//	for (SListNode *cur = list->first; cur != NULL; cur = cur->next) {
//		if (cur->data == data) {
//			return cur;
//		}
//	}
//
//	// 没找到
//	return NULL;
//}
//
//// 插入元素
//void SListInsertAfter(SListNode *pos, SLDataType data)
//{
//	SListNode *node = BuySListNode(data);
//	node->next = pos->next;
//	pos->next = node;
//}
//
//// 删除元素
//void SListEraseAfter(SListNode *pos)
//{
//	SListNode *next = pos->next->next;	// next 是 D
//	free(pos->next);
//	pos->next = next;
//}
//
//// 删除值为data的节点
//void SListRemove(SList *list, SLDataType data)
//{
//	// 重点是找到 data 这个结点的前一个结点
//	// previous	prev
//
//	SListNode *prev = NULL;
//	SListNode *cur = list->first;
//
//	while (cur != NULL && cur->data != data) {
//		prev = cur;
//		cur = cur->next;
//	}
//
//	// cur == NULL 表示没找到
//	// cur != NULL && prev != NULL
//	// cur 就是要删的结点，同时 prev 就是要删的前一个结点
//	// cur != NULL && prev == NULL 头删
//	if (cur == NULL) {
//		return;
//	}
//
//	if (prev == NULL) {
//		SListPopFront(list);
//		return;
//	}
//
//	prev->next = cur->next;
//	free(cur);
//}
//
//// 遍历打印单链表
//void SListPrint(SList *list)
//{
//	for (SListNode *cur = list->first; cur != NULL; cur = cur->next) {
//		printf("%d --> ", cur->data);
//	}
//	printf("NULL\n");
//}
//
//
////void main() {
////	char x;
////	bool flag2 = 0;
////	DisplayMainMenu();
////	do {
////		do {
////			cin >> x;
////			if ((x >= 'a'&&x <= 'z'))flag2 = 1;
////			else {
////				cout << "指令错误!!!!!!!!!!" << endl;
////				cout << " 请选择相应的数字进行操作: " << endl;
////			}
////		} while (flag2 == 0);
////		switch (x) {
////		case 'a':
////			cout << "******************************现在进行学生信息录入******************************\n";
////			InputScore();
////			cout << "输入的学生信息为：" << endl;
////			ShowStudentInfo();
////			cout << "********************************************************************************\n";
////			DisplayMainMenu();
////			break;
////		case 'b': {
////			char z;
////			cout << "******************************现在进行学生信息查询******************************\n";
////			cout << "请选择查询方式：" << endl;
////			cout << "(0)--按姓名查询；   (1)--按学号查询；" << endl;
////			cin >> z;
////			while (z != '0'&&z != '1') {
////				cout << "指令错误(请选择(0)或者(1))!!!!!!!" << endl;
////				cout << "请选择查询方式：(0)--按姓名查询；   (1)--按学号查询；";
////				cin >> z;
////			}
////			switch (z) {
////			case '0':SearchByName(); break;//按姓名查询
////			case '1':SearchByNumber(); break;//按学号查询
////			}
////			cout << "********************************************************************************\n";
////			DisplayMainMenu();
////			break;
////		}
////		case 'c': {
////			char p;
////			cout << "******************************现在进行学生信息修改******************************\n";
////			cout << "请选择修改方式：(0)--按姓名修改；     (1)--按学号修改；" << endl;
////			cin >> p;
////			while (p != '0'&&p != '1') {
////				cout << "指令错误(请选择(0)或者(1))!!!!!!!" << endl;
////				cout << "请选择修改方式：(0)--按姓名修改；     (1)--按学号修改；" << endl;
////				cin >> p;
////			}
////			switch (p) {
////			case  '0': EditByName(); break;//按姓名修改
////			case  '1': EditByNumber(); break;//按学号修改 
////			}
////			cout << "********************************************************************************\n";
////			DisplayMainMenu();
////			break;
////		}
////		case 'd':
////			cout << "******************************现在进行学生信息删除******************************\n";
////			Delete();//删除
////			ShowStudentInfo();
////			cout << "********************************************************************************\n";
////			DisplayMainMenu();
////			break;
////		case 'e':
////			cout << "******************************现在进行显示学生信息******************************\n";
////			ShowStudentInfo(); //显示数据 	    
////			cout << "********************************************************************************\n";
////			DisplayMainMenu();
////			break;
////		case 'f':
////			cout << "******************************现在进行保存学生信息******************************\n";
////			save();//保存学生信息		    
////			cout << "********************************************************************************\n";
////			DisplayMainMenu();
////			break;
////		case 'g':
////			cout << "******************************现在进行读取学生信息******************************\n";
////			FreadFile();
////			cout << "********************************************************************************\n";
////			DisplayMainMenu();
////			break;
////		case 'h':
////			cout << "********************************************************************************\n";
////			cout << " 您已退出学生成绩管理系统, 谢谢您的使用! \n";
////			cout << "********************************************************************************\n";
////			cout << endl;
////			exit(0);
////			break;
////		case 'i':
////			cout << "********************************************************************************\n";
////			cout << "*****************************现在进行插入学生信息*********************************\n";
////			Insert();
////			cout << "********************************************************************************\n";
////			DisplayMainMenu();
////			break;
////		}
////	} while (flag2 == 1);
////}
//
//
//void TestSList1()
//{
//	SList list;
//	SListInit(&list);
//
//	SListPrint(&list);
//
//	SListPushFront(&list, 3);
//	SListPushFront(&list, 2);
//	SListPushFront(&list, 1);
//	SListPrint(&list);
//
//	SListPopFront(&list);
//	SListPopFront(&list);
//
//	SListPrint(&list);
//
//	SListPopFront(&list);
//	SListPrint(&list);
//
//	SListPushBack(&list, 4);
//	SListPushBack(&list, 5);
//	SListPushBack(&list, 6);
//	SListPrint(&list);
//
//	SListPopBack(&list);
//	SListPrint(&list);
//	SListPopBack(&list);
//	SListPrint(&list);
//	SListPopBack(&list);
//	SListPrint(&list);
//}
//
//void TestSList2() {
//
//	SList list;
//	SListInit(&list);
//
//	SListPushBack(&list, 1);
//	SListPushBack(&list, 2);
//	SListPushBack(&list, 3);
//	SListPushBack(&list, 4);
//	SListPushBack(&list, 5);
//	SListPrint(&list);
//
//	// 3 后面插入 10
//	SListNode *n3 = SListFind(&list, 3);
//	SListInsertAfter(n3, 10);
//	SListPrint(&list);
//
//	SListEraseAfter(n3);
//	SListPrint(&list);
//}
//
//void TestSList3()
//{
//	SList list;
//	SListInit(&list);
//
//	SListPushBack(&list, 1);
//	SListPushBack(&list, 2);
//	SListPushBack(&list, 3);
//	SListPushBack(&list, 4);
//	SListPushBack(&list, 5);
//	SListPrint(&list);
//
//
//	SListRemove(&list, 3);
//	SListPrint(&list);
//
//	SListRemove(&list, 1);
//	SListPrint(&list);
//
//	SListRemove(&list, 5);
//	SListPrint(&list);
//}
//
//int main() {
//	TestSList3();
//	system("pause");
//	return 0;
//}

