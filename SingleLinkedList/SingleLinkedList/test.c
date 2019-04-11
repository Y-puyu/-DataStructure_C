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

// 初始化单链表
void SListInit(SList *list)
{
	assert(list != NULL);
	list->first = NULL;
}

// 销毁单链表
void SListDestroy(SList *list)
{
	SListNode *next;
	for (SListNode *cur = list->first; cur != NULL; cur = next) {
		next = cur->next;
		free(cur);
	}

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

// 遍历打印单链表
void SListPrint(SList *list)
{
	for (SListNode *cur = list->first; cur != NULL; cur = cur->next) {
		printf("%d --> ", cur->data);
	}
	printf("NULL\n");
}

void menu() {
	printf("  a：建立单链表\n");
	printf("  b：遍历打印单链表\n");
	printf("  c：逆置单链表\n");
	printf("  d：非递减有序单链表\n");
	printf("  e：非递减有序单链表中插入一个元素使链表仍然有序\n");
	printf("  f：在非递减有序链表中删除值为x的结点\n");
}

//void main() {
//	char x;
//	bool flag2 = 0;
//	DisplayMainMenu();
//	do {
//		do {
//			cin >> x;
//			if ((x >= 'a'&&x <= 'z'))flag2 = 1;
//			else {
//				cout << "指令错误!!!!!!!!!!" << endl;
//				cout << " 请选择相应的数字进行操作: " << endl;
//			}
//		} while (flag2 == 0);
//		switch (x) {
//		case 'a':
//			cout << "******************************现在进行学生信息录入******************************\n";
//			InputScore();
//			cout << "输入的学生信息为：" << endl;
//			ShowStudentInfo();
//			cout << "********************************************************************************\n";
//			DisplayMainMenu();
//			break;
//		case 'b': {
//			char z;
//			cout << "******************************现在进行学生信息查询******************************\n";
//			cout << "请选择查询方式：" << endl;
//			cout << "(0)--按姓名查询；   (1)--按学号查询；" << endl;
//			cin >> z;
//			while (z != '0'&&z != '1') {
//				cout << "指令错误(请选择(0)或者(1))!!!!!!!" << endl;
//				cout << "请选择查询方式：(0)--按姓名查询；   (1)--按学号查询；";
//				cin >> z;
//			}
//			switch (z) {
//			case '0':SearchByName(); break;//按姓名查询
//			case '1':SearchByNumber(); break;//按学号查询
//			}
//			cout << "********************************************************************************\n";
//			DisplayMainMenu();
//			break;
//		}
//		case 'c': {
//			char p;
//			cout << "******************************现在进行学生信息修改******************************\n";
//			cout << "请选择修改方式：(0)--按姓名修改；     (1)--按学号修改；" << endl;
//			cin >> p;
//			while (p != '0'&&p != '1') {
//				cout << "指令错误(请选择(0)或者(1))!!!!!!!" << endl;
//				cout << "请选择修改方式：(0)--按姓名修改；     (1)--按学号修改；" << endl;
//				cin >> p;
//			}
//			switch (p) {
//			case  '0': EditByName(); break;//按姓名修改
//			case  '1': EditByNumber(); break;//按学号修改 
//			}
//			cout << "********************************************************************************\n";
//			DisplayMainMenu();
//			break;
//		}
//		case 'd':
//			cout << "******************************现在进行学生信息删除******************************\n";
//			Delete();//删除
//			ShowStudentInfo();
//			cout << "********************************************************************************\n";
//			DisplayMainMenu();
//			break;
//		case 'e':
//			cout << "******************************现在进行显示学生信息******************************\n";
//			ShowStudentInfo(); //显示数据 	    
//			cout << "********************************************************************************\n";
//			DisplayMainMenu();
//			break;
//		case 'f':
//			cout << "******************************现在进行保存学生信息******************************\n";
//			save();//保存学生信息		    
//			cout << "********************************************************************************\n";
//			DisplayMainMenu();
//			break;
//		case 'g':
//			cout << "******************************现在进行读取学生信息******************************\n";
//			FreadFile();
//			cout << "********************************************************************************\n";
//			DisplayMainMenu();
//			break;
//		case 'h':
//			cout << "********************************************************************************\n";
//			cout << " 您已退出学生成绩管理系统, 谢谢您的使用! \n";
//			cout << "********************************************************************************\n";
//			cout << endl;
//			exit(0);
//			break;
//		case 'i':
//			cout << "********************************************************************************\n";
//			cout << "*****************************现在进行插入学生信息*********************************\n";
//			Insert();
//			cout << "********************************************************************************\n";
//			DisplayMainMenu();
//			break;
//		}
//	} while (flag2 == 1);
//}





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

//int main() {
//	TestSList3();
//	system("pause");
//	return 0;
//}


int main() {
	SList list;
	menu();

	while (1) {

	}


	system("pause");
	return 0;
}