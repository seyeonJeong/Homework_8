/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
	printf("[-----[������] [2018038027] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h){

	listNode* p;
	listNode* prev = NULL;
	p = h->rlink; // p�� �������� rlink�� ����Ű�� ��尡 ��

	while (p!= NULL && p != h) // p�� NULL���� ���ų� p�� h�� ������
	{
		prev = p; // prev�� p�� ��
		p = p->rlink; // p�� p�� rlink�� ����Ű�� ��尡 ��
		prev->llink = prev; // prev�� llink�� �ڱ��ڽ��̵�
		prev->rlink = prev; // prev�� rlink�� �ڱ��ڽ��� ��
		free(prev); // prev�� ������
	}
	free(h); // �����带 ����

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {//�������� ���� NULL�̶��
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; // p�� �������� rlink�� ����Ű�� ������ ����

	while (p != NULL && p != h) {//p�� NULL���̰� p�� �����尡 �϶�����
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; // p�� ���� p�� rlink�� ����Ű�� ������ ����
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink; // �������� rlink�� ����Ű�� ���� p�� ����
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink; // p�� ����Ű�� ��带 p�� rlink�� ����Ű�� ���� ����
		i++;
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {

	listNode* n1 = (listNode*)malloc(sizeof(listNode)); // �����Ҵ��� �̿��Ͽ� n1 ��带 ����
	listNode* cur = h->rlink; // Ž���� �� ����ϴ� ��带 ����Ű�� ������ cur�� �����尡 ����Ű�� ������ ����

	n1->key = key;//n1�� key���� �Ű������� ������ key���� ����

	if (h->rlink == h)//ù��° �����尡 ����Ű�� ���� ��������, �� ��尡 ���� ���¶��
	{
		n1->llink = h; // n1�� llink�� h�� ����Ű�� �ϰ�
		n1->rlink = h;//n1�� rlink�� h�� ����Ű���� (n1�� ù��° ����� ��������Ʈ�̹Ƿ� rlink�� �����带 �����Ѿ���)
		h->rlink = n1;//h�� rlink�� n1�� ����Ű����
		h->llink = n1;//h�� llink�� n1�� ����Ŵ(n1�� ù��° ������� ������ ����� �������� llink�� ������ ��带 �����Ѿ���)
		return 0;
	}
	while (cur->rlink != h) // cur�� rlink���� �����尡 �ƴҶ� ���� �ݺ�
	{
		cur = cur->rlink; // cur�� cur�� rlink�� ����Ű�� ���� ����
	}

	//������ ���߿��Ḯ��Ʈ�� ��������� n1�� rlink�� ����Ű�� ���� ������� �������ְ� �������� llink�� ����Ű�� ���� n1���� �������ָ鼭 ��������Ʈ�� Ư¡�� ���� �ϴ� �۾�.
	n1->llink = cur; // n1�� llink�� ����Ű�� ���� cur�� ��.
	n1->rlink = h; //n1�� rlink�� ����Ű�� ���� �����尡 ��.
	cur->rlink = n1; //cur�� rlink�� ����Ű�� ���� n1�� ��.
	h->llink = n1; //h�� llink�� ����Ű�� ���� n1�� ��.

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	listNode* storage; // ������ ��带 �����ϴ� ��带 ����Ű�� ������ storage�� ������
	listNode* cur = h->rlink; // Ž���� �ʿ��� ��带 ����Ű�� ������ cur�� �����ϰ� �����尡 ����Ű�� ��带 ����

	while (cur != h) // cur == �������϶�����
	{
		if (h->rlink == h) // ���� �����尡 ����Ű�� ���� �ڱ��ڽ��̸�
		{
			printf("������ ��尡 �����ϴ�.\n");
			return 0;
		}
		if (cur->rlink == h) // cur�� ����Ű�� ���� NULL�̶��
		{
			storage = cur; // cur�� storage�� �����Ѵ�.
			cur->llink->rlink = cur->rlink; // ���� cur�� rlink�� ����Ű�� ��带 cur�� rlink�� ����Ű�� ���� �ٲ۴�.
			h->llink = cur->llink; // ������ ��带 ���������Ƿ�, cur�� �������� llink���� cur�� �������� �ٲ��ش�.(������尡 ������ ��尡 ��.)
			storage->rlink = NULL; // ������ ����� rlink���� NULL�� ����
			storage->llink = NULL; // ������ ����� llink���� NULL�� ����
			free(storage); // storage�� ����� ��带 ����
			return 0;
		}
		cur = cur->rlink; // cur��带 cur�� rlink�� ����Ű�� ���� ����
	}




	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // �����Ҵ��� �̿��Ͽ� ������
	node->key = key; // ����� key���� �Ű������� ���� key���� ����
	if (h->llink == h) // �������� �������� ��������(��, ��尡 ���ٸ�)
	{
		node->rlink = h->rlink; // node�� rlink�� ����Ű�� ���� �������� rlink�� ����Ű�� ������ �ٲ���
		node->llink = h; // node�� llink�� ����Ű�� ���� ������� �ٲ���
		h->llink = node; // �������� llink�� ����Ű�� ���� node�� �ٲ���
		h->rlink = node; // �������� rllink�� ����Ű�� ���� node�� �ٲ���
		return 0;
	}
	//list�� ó���� ��带 �߰��ؾ��ϹǷ� �߰��� ����� llink���� ������ rlink���� �������� rlink�� ����Ű�� ���� �����ϰ� ���� ù��° ����� llink�� �߰��� ���� �ٲ��ش�.
	h->rlink->llink = node; // �������� rlink�� ����Ű�� ����� llink�� ����Ű�� ��带 node�� �ٲ���
	node->rlink = h->rlink; // node ��尡 �����尡 ����Ű�� ��带 ����Ű����
	node->llink = h; //node ����� llink�� ����Ű�� ���� ������� �ٲ���
	h->rlink = node; // �����尡 node�� ����Ű����.

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	listNode* storage; // ��带 ����Ű�� �����͸� ����, ������ ��带 �����ϴ� �뵵
	if (h->rlink == h) // ���� �����尡 ����Ű�� ��尡 NULL�� ��� (��尡 ���� ���)
	{
		printf("������ ��尡 �����ϴ�.\n");
		return 0;
	}
	else
	{
		storage = h->rlink; // ������ ��带 ���� ù��° ��带 �����ؾ��ϹǷ� �����尡 ����Ű�� ��带 ����
		h->rlink = h->rlink->rlink; // �����尡 ����Ű�� ��带 �����尡 ����Ű�� ����� rlink�� ����Ű�� ���� ���� (�ι�° ��带 ù��° ����� ������ �ϰ� ����� �۾�)
		h->rlink->llink = h; // �������� rlink�� ����Ű�� ����� llink�� ������� �ٲ��ش�.
		return 0;
	}
	storage->rlink = NULL; // ������ ����� rlink���� NULL�� ����
	storage->llink = NULL; // ������ ����� llink���� NULL�� ����
	free(storage); // ��带 ����





	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {

	listNode* cur = h; // �����尡 ����Ű�� ��带 ����Ű�� �����͸� ������
	listNode* previous = cur->llink; // ���� ��带 ����Ű�� �����͸� �����ϰ� �ʱ�ȭ
	listNode* trail = previous->llink; // ��������� ������带 ����Ű�� �����͸� �����ϰ� �ʱ�ȭ

	if (h->rlink == h) // h�� rlink�� ����Ű�� ��尡 �ڱ��ڽ��� ���
	{
		printf("��尡 �����ϴ�.\n");
		return 0;
	}
	while (cur->rlink != h) // cur�� rlink�� ����Ű�� ��尡 ������ �϶�����
	{
		trail = previous; //trail�� ���� previous �� ���� ��尡 ��
		previous = cur; // ���� ����� ���� ���� ��尡 ��
		cur = cur->rlink; // ���� ����� ���� ���� ����� rlink�� ����Ű�� ��尡 ��
		previous->llink = cur; // ���� ����� llink�� ����Ű�� ���� ���� ��尡 ��
		previous->rlink = trail; // ���� ����� rlink�� ����Ű�� ���� previous�� ������尡 ��
	}
	cur->rlink = previous; // cur->rlink�� �������̸� cur�� rlink�� ����Ű�� ���� previous�� ��

	return 0;
}



/**
 *  ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ����
 **/
int insertNode(listNode* h, int key) {

	listNode* cur = h->rlink; //Ž���� ���� cur�̶�� ��带 ����Ű�� �����͸� �����ϰ� ����Ʈ�� first�� ����Ű����
	listNode* n1 = (listNode*)malloc(sizeof(listNode));//�����Ҵ��� �̿��Ͽ� n1��带 ����
	n1->key = key;// n1����� key���� �Ű������� ���� key���� ����

	if (h->rlink == h)//���� �����尡 ����Ű�� ��尡 �ڱ��ڽ��̶��(��尡 ����)
	{
		h->rlink = n1;// �������� rlink�� n1�� ����Ű���ϰ�
		h->llink = n1;//�������� llink�� n1�� ����Ű����
		n1->rlink = h;// n1�� rlink��  h�� ����Ű���� (n1�� ù��° ���� ��������, ���� ����Ʈ)
		n1->llink = h; // n1�� llink�� h�� ����Ű����

		return 0;
	}
	else if (h->rlink->key >= n1->key)//�����尡 ����Ű�� ����� key ���� n1�� key������ ũ�ų� �������
	{
		n1->rlink = h->rlink;// n1�� rlink�� ����Ű�� ��尡 �����尡 ����Ű�� ��尡��.
		h->rlink->llink = n1;
		n1->llink = h; // n1�� llink�� ����Ű�� ��尡 �����尡��.
		h->rlink = n1;// �����尡 ����Ű�� ���� n1��尡 ��.
		return 0;
	}
	while (cur->rlink != h)//cur�� rlink�� ����Ű�� ��尡 �������϶����� �ݺ�
	{
		if (cur->key > n1->key)// ���� cur�� key���� n1�� key������ ū���
		{
			n1->rlink = cur;//n1����� rlink�� ����Ű�� ���� cur�̵�.
			n1->llink = cur->llink; // n1����� llink�� ����Ű�� ���� cur����� llink�� ����Ű�� ���̵�. �� cur�� ������带 n1�� llink�� ����Ŵ
			cur->llink->rlink = n1; //cur����� llink�� ����Ű�� ����� rlink ���� n1��尡 ��
			cur->llink = n1;//cur����� llink�� ����Ű�� ���� n1�� ��.

			return 0;
		}
		if (cur->key == n1->key)// ���� cur�� key���� n1�� key ���� �������
		{
			n1->rlink = cur;//n1����� rlink�� ����Ű�� ��尡 cur�̵�.
			cur->llink->rlink = n1;//cur����� llink�� ����Ű�� ����� rlink�� ����Ű�� ��尡 n1�� ��.
			n1->llink = cur->llink; // n1�� llink�� ����Ű�� ��尡 cur�� ������尡 ��
			cur->llink = n1;//cur����� llink�� ����Ű�� ��尡 n1�� ��.

			return 0;
		}
		cur = cur->rlink; // cur��带 cur�� rlink�� ����Ű�� ���� ���� (�������� �̵�)
	}
	//����Ʈ�� ���� �����ϴ� �۾�(����Ʈ�� n1�� key������ ū key���� ���� ��尡 �������� ����)
	n1->llink = cur; // n1�� llink�� ����Ű�� ���� cur�� ��.
	n1->rlink = h; //n1�� rlink�� ����Ű�� ���� �����尡 ��.
	cur->rlink = n1; //cur�� rlink�� ����Ű�� ���� n1�� ��.
	h->llink = n1; //h�� llink�� ����Ű�� ���� n1�� ��.
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	listNode* n1 = (listNode*)malloc(sizeof(listNode));// �����Ҵ��� �̿��Ͽ� ��带 ����Ű�� ������ n1�� ����
	listNode* cur = h->rlink;// Ž���� �ʿ��� ��带 ����Ű�� ������ cur�� �����ϰ� �����尡 ����Ű�� ��带 ����
	listNode* storage;// ������ ��带 �����ϴ� ��带 ����Ű�� ������ storage�� ������

	if (h->rlink == h) // h�� rlink�� ����Ű�� ���� �ڱ��ڽ��̸�
	{
		printf("������ ��尡 �����ϴ�.\n");
		return 0;
	}
	while (cur->rlink != h)//cur�� rlink���� h�϶����� �ݺ�
	{
		if (h->rlink->key == key)//�����尡 ����Ű�� ����� key���� key���� ���
		{
			storage = h->rlink; // ������ ��带 ���� ù��° ��带 �����ؾ��ϹǷ� �����尡 ����Ű�� ��带 ����
			h->rlink = h->rlink->rlink; // �����尡 ����Ű�� ��带 �����尡 ����Ű�� ����� rlink�� ����Ű�� ���� ���� (�ι�° ��带 ù��° ����� ������ �ϰ� ����� �۾�)
			h->rlink->llink = h; // �������� rlink�� ����Ű�� ����� llink�� ������� �ٲ��ش�.

			storage->rlink = NULL; // ������ ����� rlink�� ����Ű�� ���� NULL�� ����
			storage->llink = NULL; // ������ ����� llink�� ����Ű�� ���� NULL�� ����

			free(storage); // ��带 ����
			return 0;
		}
		if (cur->key == key) // cur�� key���� key�� ������
		{
			storage = cur;// storage�� cur��带 ����
			cur->llink->rlink = cur->rlink;// ����cur����� rlink�� ����Ű�� ���� ���� cur����� rlink�� ����Ű�� ������ ����
			cur->rlink->llink = cur->llink;
			storage->rlink = NULL; // ������ ����� rlink���� NULL�� ����
			storage->llink = NULL; // ������ ����� llink���� NULL�� ����
			free(storage); // ��带 ����

			return 0;
		}

		cur = cur->rlink; // cur��带 cur ����� rlink�� ����Ű�� ������ ����
	}

	storage = cur; // cur�� storage�� �����Ѵ�.
	cur->llink->rlink = cur->rlink; // ���� cur�� rlink�� ����Ű�� ��带 cur�� rlink�� ����Ű�� ���� �ٲ۴�.
	h->llink = cur->llink; // ������ ��带 ���������Ƿ�, cur�� �������� llink���� cur�� �������� �ٲ��ش�.(������尡 ������ ��尡 ��.)
	storage->rlink = NULL; // ������ ����� rlink���� NULL�� ����
	storage->llink = NULL; // ������ ����� llink���� NULL�� ����
	free(storage); // storage�� ����� ��带 ����

	return 0;
}
