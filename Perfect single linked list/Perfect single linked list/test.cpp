
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
void SListInit(SList *list)
{
	assert(list != NULL);
	list->first = NULL;
}


// ���뵥����ڵ�ռ�
SListNode * BuySListNode(SLDataType data)
{
	SListNode *node = (SListNode *)malloc(sizeof(SListNode));
	assert(node != NULL);
	node->data = data;
	node->next = NULL;

	return node;
}

// ������ͷ��
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

// ������ͷɾ
void SListPopFront(SList *list)
{
	assert(list);	// û������
	assert(list->first != NULL);	// ���������������ǿյ�

	SListNode *old_first = list->first;
	list->first = list->first->next;
	free(old_first);
}

// ɾ��ֵΪdata�Ľڵ�
void SListRemove(SList *list)
{
	printf("������Ҫɾ��������Ԫ�أ� ");
	// �ص����ҵ� data �������ǰһ�����
	// previous	prev
	SLDataType data;
	cin >> data;
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
void SListInsertAfter(SList *list)
{
	SListNode *prev;
	SLDataType data;
	printf("���������֣� ");
	cin >> data;
	SListPushFront(list, data);
	SListSort(list);
}

void ReverseList(SList* list) {
	SListNode *newHead = NULL;
	SListNode *node;

	while (list-> first!= NULL) {
		// ��֮ǰ��������ͷɾ
		node = list->first;
		list->first = list->first->next;

		// ����������ͷ��
		node->next = newHead;
		newHead = node;
	}
	list->first = newHead;
}

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
//// ��ʼ��������
//void SListInit(SList *list)
//{
//	assert(list != NULL);
//	list->first = NULL;
//}
//
//// ���ٵ�����
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
//// ���뵥����ڵ�ռ�
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
//// ������ͷ��
//void SListPushFront(SList *list, SLDataType data)
//{
//	assert(list != NULL);
//
//	// 1. Node �ռ�
//	SListNode *node = BuySListNode(data);
//	// 2. �µĵ�һ��������һ��������ԭ���ĵ�һ�����
//	node->next = list->first;
//	// 3. ��¼�µĵ�һ�����
//	list->first = node;
//}
//
//// ������ͷɾ
//void SListPopFront(SList *list)
//{
//	assert(list);	// û������
//	assert(list->first != NULL);	// ���������������ǿյ�
//
//	SListNode *old_first = list->first;
//	list->first = list->first->next;
//	free(old_first);
//}
//
//// ������β��
//void SListPushBack(SList *list, SLDataType data)
//{
//	assert(list != NULL);
//
//	if (list->first == NULL) {
//		// ����Ϊ��
//		SListPushFront(list, data);
//		return;
//	}
//
//	// �������Ѿ��н������
//	// �����һ�����
//	SListNode *lastone = list->first;
//	for (; lastone->next != NULL; lastone = lastone->next) {
//	}
//	// lastone �������һ�����
//
//	// ����ռ�
//	SListNode *node = BuySListNode(data);
//	lastone->next = node;
//}
//
//// ������βɾ
//void SListPopBack(SList *list)
//{
//	assert(list != NULL);
//	assert(list->first != NULL);	// 0 ��
//
//	if (list->first->next == NULL) {
//		// 1 ��
//		SListPopFront(list);
//		return;
//	}
//
//	// ͨ����� >= 2 ��
//	SListNode *cur;
//	for (cur = list->first; cur->next->next != NULL; cur = cur->next) {
//	}
//	// cur ���ǵ����ڶ������
//	free(cur->next);
//	cur->next = NULL;
//}
//
//// ���ҵ�����Ԫ��
//SListNode * SListFind(SList *list, SLDataType data)
//{
//	for (SListNode *cur = list->first; cur != NULL; cur = cur->next) {
//		if (cur->data == data) {
//			return cur;
//		}
//	}
//
//	// û�ҵ�
//	return NULL;
//}
//
//// ����Ԫ��
//void SListInsertAfter(SListNode *pos, SLDataType data)
//{
//	SListNode *node = BuySListNode(data);
//	node->next = pos->next;
//	pos->next = node;
//}
//
//// ɾ��Ԫ��
//void SListEraseAfter(SListNode *pos)
//{
//	SListNode *next = pos->next->next;	// next �� D
//	free(pos->next);
//	pos->next = next;
//}
//
//// ɾ��ֵΪdata�Ľڵ�
//void SListRemove(SList *list, SLDataType data)
//{
//	// �ص����ҵ� data �������ǰһ�����
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
//	// cur == NULL ��ʾû�ҵ�
//	// cur != NULL && prev != NULL
//	// cur ����Ҫɾ�Ľ�㣬ͬʱ prev ����Ҫɾ��ǰһ�����
//	// cur != NULL && prev == NULL ͷɾ
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
//// ������ӡ������
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
////				cout << "ָ�����!!!!!!!!!!" << endl;
////				cout << " ��ѡ����Ӧ�����ֽ��в���: " << endl;
////			}
////		} while (flag2 == 0);
////		switch (x) {
////		case 'a':
////			cout << "******************************���ڽ���ѧ����Ϣ¼��******************************\n";
////			InputScore();
////			cout << "�����ѧ����ϢΪ��" << endl;
////			ShowStudentInfo();
////			cout << "********************************************************************************\n";
////			DisplayMainMenu();
////			break;
////		case 'b': {
////			char z;
////			cout << "******************************���ڽ���ѧ����Ϣ��ѯ******************************\n";
////			cout << "��ѡ���ѯ��ʽ��" << endl;
////			cout << "(0)--��������ѯ��   (1)--��ѧ�Ų�ѯ��" << endl;
////			cin >> z;
////			while (z != '0'&&z != '1') {
////				cout << "ָ�����(��ѡ��(0)����(1))!!!!!!!" << endl;
////				cout << "��ѡ���ѯ��ʽ��(0)--��������ѯ��   (1)--��ѧ�Ų�ѯ��";
////				cin >> z;
////			}
////			switch (z) {
////			case '0':SearchByName(); break;//��������ѯ
////			case '1':SearchByNumber(); break;//��ѧ�Ų�ѯ
////			}
////			cout << "********************************************************************************\n";
////			DisplayMainMenu();
////			break;
////		}
////		case 'c': {
////			char p;
////			cout << "******************************���ڽ���ѧ����Ϣ�޸�******************************\n";
////			cout << "��ѡ���޸ķ�ʽ��(0)--�������޸ģ�     (1)--��ѧ���޸ģ�" << endl;
////			cin >> p;
////			while (p != '0'&&p != '1') {
////				cout << "ָ�����(��ѡ��(0)����(1))!!!!!!!" << endl;
////				cout << "��ѡ���޸ķ�ʽ��(0)--�������޸ģ�     (1)--��ѧ���޸ģ�" << endl;
////				cin >> p;
////			}
////			switch (p) {
////			case  '0': EditByName(); break;//�������޸�
////			case  '1': EditByNumber(); break;//��ѧ���޸� 
////			}
////			cout << "********************************************************************************\n";
////			DisplayMainMenu();
////			break;
////		}
////		case 'd':
////			cout << "******************************���ڽ���ѧ����Ϣɾ��******************************\n";
////			Delete();//ɾ��
////			ShowStudentInfo();
////			cout << "********************************************************************************\n";
////			DisplayMainMenu();
////			break;
////		case 'e':
////			cout << "******************************���ڽ�����ʾѧ����Ϣ******************************\n";
////			ShowStudentInfo(); //��ʾ���� 	    
////			cout << "********************************************************************************\n";
////			DisplayMainMenu();
////			break;
////		case 'f':
////			cout << "******************************���ڽ��б���ѧ����Ϣ******************************\n";
////			save();//����ѧ����Ϣ		    
////			cout << "********************************************************************************\n";
////			DisplayMainMenu();
////			break;
////		case 'g':
////			cout << "******************************���ڽ��ж�ȡѧ����Ϣ******************************\n";
////			FreadFile();
////			cout << "********************************************************************************\n";
////			DisplayMainMenu();
////			break;
////		case 'h':
////			cout << "********************************************************************************\n";
////			cout << " �����˳�ѧ���ɼ�����ϵͳ, лл����ʹ��! \n";
////			cout << "********************************************************************************\n";
////			cout << endl;
////			exit(0);
////			break;
////		case 'i':
////			cout << "********************************************************************************\n";
////			cout << "*****************************���ڽ��в���ѧ����Ϣ*********************************\n";
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
//	// 3 ������� 10
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

