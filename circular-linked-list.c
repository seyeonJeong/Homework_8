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
	printf("[-----[정세연] [2018038027] -----]\n");

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

	listNode* storage; // 삭제할 노드를 저장하는 노드를 가리키는 포인터 storage를 생성함
	listNode* cur = h->rlink; // 탐색에 필요한 노드를 가리키는 포인터 cur을 생성하고 헤더노드가 가리키는 노드를 저장

	while (cur != h) // cur == 헤더노드일때까지
	{
		if (h->rlink == h) // 만약 헤더노드가 가리키는 값이 자기자신이면
		{
			printf("삭제할 노드가 없습니다.\n");
			return 0;
		}
		if (cur->rlink == h) // cur이 가리키는 값이 NULL이라면
		{
			storage = cur; // cur을 storage에 저장한다.
			cur->llink->rlink = cur->rlink; // 이전 cur의 rlink가 가리키는 노드를 cur의 rlink가 가리키는 노드로 바꾼다.
			h->llink = cur->llink; // 마지막 노드를 삭제했으므로, cur의 헤더노드의 llink값을 cur의 이전노드로 바꿔준다.(이전노드가 마지막 노드가 됨.)
			storage->rlink = NULL; // 삭제할 노드의 rlink값을 NULL로 설정
			storage->llink = NULL; // 삭제할 노드의 llink값을 NULL로 설정
			free(storage); // storage에 저장된 노드를 해제
			return 0;
		}
		cur = cur->rlink; // cur노드를 cur의 rlink가 가리키는 노드로 변경
	}




	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 동적할당을 이용하여 노드생성
	node->key = key; // 노드의 key값에 매개변수로 받은 key값을 대입
	if (h->llink == h) // 헤더노드의 다음값이 헤더노드라면(즉, 노드가 없다면)
	{
		node->rlink = h->rlink; // node의 rlink가 가리키는 값을 헤더노드의 rlink가 가리키는 값으로 바꿔줌
		node->llink = h; // node의 llink가 가리키는 값을 헤더노드로 바꿔줌
		h->llink = node; // 헤더노드의 llink가 가리키는 값을 node로 바꿔줌
		h->rlink = node; // 헤더노드의 rllink가 가리키는 값을 node로 바꿔줌
		return 0;
	}
	//list의 처음에 노드를 추가해야하므로 추가할 노드의 llink값은 헤더노드 rlink값은 헤더노드의 rlink가 가리키던 노드로 변경하고 원래 첫번째 노드의 llink를 추가할 노드로 바꿔준다.
	h->rlink->llink = node; // 헤더노드의 rlink가 가리키는 노드의 llink가 가리키는 노드를 node로 바꿔줌
	node->rlink = h->rlink; // node 노드가 헤더노드가 가리키는 노드를 가리키게함
	node->llink = h; //node 노드의 llink가 가리키는 값을 헤더노드로 바꿔줌
	h->rlink = node; // 헤더노드가 node를 가리키게함.

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	listNode* storage; // 노드를 가리키는 포인터를 정의, 삭제할 노드를 저장하는 용도
	if (h->rlink == h) // 만약 헤더노드가 가리키는 노드가 NULL일 경우 (노드가 없을 경우)
	{
		printf("삭제할 노드가 없습니다.\n");
		return 0;
	}
	else
	{
		storage = h->rlink; // 삭제할 노드를 저장 첫번째 노드를 삭제해야하므로 헤더노드가 가리키는 노드를 저장
		h->rlink = h->rlink->rlink; // 헤더노드가 가리키는 노드를 헤더노드가 가리키는 노드의 rlink로 가리키는 노드로 변경 (두번째 노드를 첫번째 노드의 역할을 하게 만드는 작업)
		h->rlink->llink = h; // 헤더노드의 rlink가 가리키는 노드의 llink를 헤더노드로 바꿔준다.
		return 0;
	}
	storage->rlink = NULL; // 삭제할 노드의 rlink값을 NULL로 변경
	storage->llink = NULL; // 삭제할 노드의 llink값을 NULL로 변경
	free(storage); // 노드를 해제





	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	listNode* cur = h; // 헤더노드가 가리키는 노드를 가리키는 포인터를 선언함
	listNode* previous = cur->llink; // 이전 노드를 가리키는 포인터를 선언하고 초기화
	listNode* trail = previous->llink; // 이전노드의 이전노드를 가리키는 포인터를 선언하고 초기화

	if (h->rlink == h) // h의 rlink가 가리키는 노드가 자기자신일 경우
	{
		printf("노드가 없습니다.\n");
		return 0;
	}
	while (cur->rlink != h) // cur의 rlink가 가리키는 노드가 헤더노드 일때까지
	{
		trail = previous; //trail의 값은 previous 즉 이전 노드가 됨
		previous = cur; // 이전 노드의 값은 현재 노드가 됨
		cur = cur->rlink; // 현재 노드의 값은 현재 노드의 rlink가 가리키는 노드가 됨
		previous->llink = cur; // 이전 노드의 llink가 가리키는 값은 현재 노드가 됨
		previous->rlink = trail; // 이전 노드의 rlink가 가리키는 노드는 previous의 이전노드가 됨
	}
	cur->rlink = previous; // cur->rlink가 헤더노드이면 cur의 rlink가 가리키는 노드는 previous가 됨

	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
 **/
int insertNode(listNode* h, int key) {

	listNode* cur = h->rlink; //탐색을 위해 cur이라는 노드를 가리키는 포인터를 생성하고 리스트의 first를 가리키게함
	listNode* n1 = (listNode*)malloc(sizeof(listNode));//동적할당을 이용하여 n1노드를 생성
	n1->key = key;// n1노드의 key값에 매개변수로 받은 key값을 대입

	if (h->rlink == h)//만약 헤더노드가 가리키는 노드가 자기자신이라면(노드가 없음)
	{
		h->rlink = n1;// 헤더노드의 rlink가 n1을 가리키게하고
		h->llink = n1;//헤더노드의 llink가 n1을 가리키게함
		n1->rlink = h;// n1의 rlink가  h을 가리키게함 (n1을 첫번째 노드로 설정해줌, 원형 리스트)
		n1->llink = h; // n1의 llink가 h를 가리키게함

		return 0;
	}
	else if (h->rlink->key >= n1->key)//헤더노드가 가리키는 노드의 key 값이 n1의 key값보다 크거나 같은경우
	{
		n1->rlink = h->rlink;// n1의 rlink가 가리키는 노드가 헤더노드가 가리키는 노드가됨.
		h->rlink->llink = n1;
		n1->llink = h; // n1의 llink가 가리키는 노드가 헤더노드가됨.
		h->rlink = n1;// 헤더노드가 가리키는 값이 n1노드가 됨.
		return 0;
	}
	while (cur->rlink != h)//cur의 rlink가 가리키는 노드가 헤더노드일때까지 반복
	{
		if (cur->key > n1->key)// 만약 cur의 key값이 n1의 key값보다 큰경우
		{
			n1->rlink = cur;//n1노드의 rlink가 가리키는 값이 cur이됨.
			n1->llink = cur->llink; // n1노드의 llink가 가리키는 값이 cur노드의 llink가 가리키는 값이됨. 즉 cur의 이전노드를 n1의 llink가 가리킴
			cur->llink->rlink = n1; //cur노드의 llink가 가리키는 노드의 rlink 값이 n1노드가 됨
			cur->llink = n1;//cur노드의 llink가 가리키는 값이 n1이 됨.

			return 0;
		}
		if (cur->key == n1->key)// 만약 cur의 key값이 n1의 key 값과 같은경우
		{
			n1->rlink = cur;//n1노드의 rlink가 가리키는 노드가 cur이됨.
			cur->llink->rlink = n1;//cur노드의 llink가 가리키는 노드의 rlink가 가리키는 노드가 n1이 됨.
			n1->llink = cur->llink; // n1의 llink가 가리키는 노드가 cur의 이전노드가 됨
			cur->llink = n1;//cur노드의 llink가 가리키는 노드가 n1이 됨.

			return 0;
		}
		cur = cur->rlink; // cur노드를 cur의 rlink가 가리키던 노드로 설정 (다음노드로 이동)
	}
	//리스트의 끝에 삽입하는 작업(리스트에 n1의 key값보다 큰 key값을 가진 노드가 존재하지 않음)
	n1->llink = cur; // n1의 llink가 가리키는 노드는 cur이 됨.
	n1->rlink = h; //n1의 rlink가 가리키는 노드는 헤더노드가 됨.
	cur->rlink = n1; //cur의 rlink가 가리키는 노드는 n1이 됨.
	h->llink = n1; //h의 llink가 가리키는 노드는 n1이 됨.
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	listNode* n1 = (listNode*)malloc(sizeof(listNode));// 동적할당을 이용하여 노드를 가리키는 포인터 n1을 생성
	listNode* cur = h->rlink;// 탐색에 필요한 노드를 가리키는 포인터 cur을 생성하고 헤더노드가 가리키는 노드를 저장
	listNode* storage;// 삭제할 노드를 저장하는 노드를 가리키는 포인터 storage를 생성함

	if (h->rlink == h) // h의 rlink가 가리키는 값이 자기자신이면
	{
		printf("삭제할 노드가 없습니다.\n");
		return 0;
	}
	while (cur->rlink != h)//cur의 rlink값이 h일때까지 반복
	{
		if (h->rlink->key == key)//헤더노드가 가리키는 노드의 key값이 key값일 경우
		{
			storage = h->rlink; // 삭제할 노드를 저장 첫번째 노드를 삭제해야하므로 헤더노드가 가리키는 노드를 저장
			h->rlink = h->rlink->rlink; // 헤더노드가 가리키는 노드를 헤더노드가 가리키는 노드의 rlink로 가리키는 노드로 변경 (두번째 노드를 첫번째 노드의 역할을 하게 만드는 작업)
			h->rlink->llink = h; // 헤더노드의 rlink가 가리키는 노드의 llink를 헤더노드로 바꿔준다.

			storage->rlink = NULL; // 삭제할 노드의 rlink가 가리키는 값을 NULL로 설정
			storage->llink = NULL; // 삭제할 노드의 llink가 가리키는 값을 NULL로 설정

			free(storage); // 노드를 해제
			return 0;
		}
		if (cur->key == key) // cur의 key값이 key와 같으면
		{
			storage = cur;// storage에 cur노드를 저장
			cur->llink->rlink = cur->rlink;// 이전cur노드의 rlink가 가리키는 값을 현재 cur노드의 rlink가 가리키는 값으로 변경
			cur->rlink->llink = cur->llink;
			storage->rlink = NULL; // 삭제할 노드의 rlink값을 NULL로 설정
			storage->llink = NULL; // 삭제할 노드의 llink값을 NULL로 설정
			free(storage); // 노드를 해제

			return 0;
		}

		cur = cur->rlink; // cur노드를 cur 노드의 rlink가 가리키는 값으로 변경
	}

	storage = cur; // cur을 storage에 저장한다.
	cur->llink->rlink = cur->rlink; // 이전 cur의 rlink가 가리키는 노드를 cur의 rlink가 가리키는 노드로 바꾼다.
	h->llink = cur->llink; // 마지막 노드를 삭제했으므로, cur의 헤더노드의 llink값을 cur의 이전노드로 바꿔준다.(이전노드가 마지막 노드가 됨.)
	storage->rlink = NULL; // 삭제할 노드의 rlink값을 NULL로 설정
	storage->llink = NULL; // 삭제할 노드의 llink값을 NULL로 설정
	free(storage); // storage에 저장된 노드를 해제

	return 0;
}
