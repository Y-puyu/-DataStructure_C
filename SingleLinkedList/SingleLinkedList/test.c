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

// ��ʼ��������
void SListInit(SList *list)
{
	assert(list != NULL);
	list->first = NULL;
}

// ���ٵ�����
void SListDestroy(SList *list)
{
	SListNode *next;
	for (SListNode *cur = list->first; cur != NULL; cur = next) {
		next = cur->next;
		free(cur);
	}

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

// ������ӡ������
void SListPrint(SList *list)
{
	for (SListNode *cur = list->first; cur != NULL; cur = cur->next) {
		printf("%d --> ", cur->data);
	}
	printf("NULL\n");
}

void menu() {
	printf("  a������������\n");
	printf("  b��������ӡ������\n");
	printf("  c�����õ�����\n");
	printf("  d���ǵݼ���������\n");
	printf("  e���ǵݼ����������в���һ��Ԫ��ʹ������Ȼ����\n");
	printf("  f���ڷǵݼ�����������ɾ��ֵΪx�Ľ��\n");
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
//				cout << "ָ�����!!!!!!!!!!" << endl;
//				cout << " ��ѡ����Ӧ�����ֽ��в���: " << endl;
//			}
//		} while (flag2 == 0);
//		switch (x) {
//		case 'a':
//			cout << "******************************���ڽ���ѧ����Ϣ¼��******************************\n";
//			InputScore();
//			cout << "�����ѧ����ϢΪ��" << endl;
//			ShowStudentInfo();
//			cout << "********************************************************************************\n";
//			DisplayMainMenu();
//			break;
//		case 'b': {
//			char z;
//			cout << "******************************���ڽ���ѧ����Ϣ��ѯ******************************\n";
//			cout << "��ѡ���ѯ��ʽ��" << endl;
//			cout << "(0)--��������ѯ��   (1)--��ѧ�Ų�ѯ��" << endl;
//			cin >> z;
//			while (z != '0'&&z != '1') {
//				cout << "ָ�����(��ѡ��(0)����(1))!!!!!!!" << endl;
//				cout << "��ѡ���ѯ��ʽ��(0)--��������ѯ��   (1)--��ѧ�Ų�ѯ��";
//				cin >> z;
//			}
//			switch (z) {
//			case '0':SearchByName(); break;//��������ѯ
//			case '1':SearchByNumber(); break;//��ѧ�Ų�ѯ
//			}
//			cout << "********************************************************************************\n";
//			DisplayMainMenu();
//			break;
//		}
//		case 'c': {
//			char p;
//			cout << "******************************���ڽ���ѧ����Ϣ�޸�******************************\n";
//			cout << "��ѡ���޸ķ�ʽ��(0)--�������޸ģ�     (1)--��ѧ���޸ģ�" << endl;
//			cin >> p;
//			while (p != '0'&&p != '1') {
//				cout << "ָ�����(��ѡ��(0)����(1))!!!!!!!" << endl;
//				cout << "��ѡ���޸ķ�ʽ��(0)--�������޸ģ�     (1)--��ѧ���޸ģ�" << endl;
//				cin >> p;
//			}
//			switch (p) {
//			case  '0': EditByName(); break;//�������޸�
//			case  '1': EditByNumber(); break;//��ѧ���޸� 
//			}
//			cout << "********************************************************************************\n";
//			DisplayMainMenu();
//			break;
//		}
//		case 'd':
//			cout << "******************************���ڽ���ѧ����Ϣɾ��******************************\n";
//			Delete();//ɾ��
//			ShowStudentInfo();
//			cout << "********************************************************************************\n";
//			DisplayMainMenu();
//			break;
//		case 'e':
//			cout << "******************************���ڽ�����ʾѧ����Ϣ******************************\n";
//			ShowStudentInfo(); //��ʾ���� 	    
//			cout << "********************************************************************************\n";
//			DisplayMainMenu();
//			break;
//		case 'f':
//			cout << "******************************���ڽ��б���ѧ����Ϣ******************************\n";
//			save();//����ѧ����Ϣ		    
//			cout << "********************************************************************************\n";
//			DisplayMainMenu();
//			break;
//		case 'g':
//			cout << "******************************���ڽ��ж�ȡѧ����Ϣ******************************\n";
//			FreadFile();
//			cout << "********************************************************************************\n";
//			DisplayMainMenu();
//			break;
//		case 'h':
//			cout << "********************************************************************************\n";
//			cout << " �����˳�ѧ���ɼ�����ϵͳ, лл����ʹ��! \n";
//			cout << "********************************************************************************\n";
//			cout << endl;
//			exit(0);
//			break;
//		case 'i':
//			cout << "********************************************************************************\n";
//			cout << "*****************************���ڽ��в���ѧ����Ϣ*********************************\n";
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
//	// 3 ������� 10
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