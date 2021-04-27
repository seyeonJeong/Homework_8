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
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
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

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	listNode* p;
	listNode* prev = NULL;
	p = h->rlink; // p는 헤더노드의 rlink가 가리키는 노드가 됨

	while (p!= NULL && p != h) // p가 NULL값을 갖거나 p가 h일 때까지
	{
		prev = p; // prev는 p가 됨
		p = p->rlink; // p는 p의 rlink가 가리키는 노드가 됨
		prev->llink = prev; // prev의 llink는 자기자신이됨
		prev->rlink = prev; // prev의 rlink는 자기자신이 됨
		free(prev); // prev를 해제함
	}
	free(h); // 헤더노드를 해제

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {//헤더노드의 값이 NULL이라면
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; // p를 헤더노드의 rlink가 가리키는 값으로 변경

	while (p != NULL && p != h) {//p가 NULL값이고 p가 헤더노드가 일때까지
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; // p의 값을 p의 rlink가 가리키는 값으로 변경
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink; // 헤더노드의 rlink가 가리키는 값을 p에 대입
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink; // p의 가리키는 노드를 p의 rlink가 가리키는 노드로 변경
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	listNode* n1 = (listNode*)malloc(sizeof(listNode)); // 동적할당을 이용하여 n1 노드를 생성
	listNode* cur = h->rlink; // 탐색할 때 사용하는 노드를 가리키는 포인터 cur을 헤더노드가 가리키는 값으로 설정

	n1->key = key;//n1의 key값에 매개변수로 가져온 key값을 저장

	if (h->rlink == h)//첫번째 헤더노드가 가리키는 값이 헤더노드라면, 즉 노드가 없는 상태라면
	{
		n1->llink = h; // n1의 llink가 h를 가리키게 하고
		n1->rlink = h;//n1의 rlink가 h를 가리키게함 (n1이 첫번째 노드라면 원형리스트이므로 rlink가 헤더노드를 가리켜야함)
		h->rlink = n1;//h의 rlink가 n1을 가리키게함
		h->llink = n1;//h의 llink도 n1을 가리킴(n1이 첫번째 노드이자 마지막 노드라면 헤더노드의 llink는 마지막 노드를 가리켜야함)
		return 0;
	}
	while (cur->rlink != h) // cur의 rlink값이 헤더노드가 아닐때 까지 반복
	{
		cur = cur->rlink; // cur을 cur의 rlink가 가리키는 노드로 변경
	}

	//삽입은 이중연결리스트와 비슷하지만 n1의 rlink가 가리키는 값을 헤더노드로 설정해주고 헤더노드의 llink가 가리키는 값을 n1으로 설정해주면서 원형리스트의 특징을 갖게 하는 작업.
	n1->llink = cur; // n1의 llink가 가리키는 노드는 cur이 됨.
	n1->rlink = h; //n1의 rlink가 가리키는 노드는 헤더노드가 됨.
	cur->rlink = n1; //cur의 rlink가 가리키는 노드는 n1이 됨.
	h->llink = n1; //h의 llink가 가리키는 노드는 n1이 됨.

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {


	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {


	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
 **/
int insertNode(listNode* h, int key) {

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	return 0;
}
