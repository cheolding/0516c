#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct ListNode { // 노드 타입을 구조체로 정의한다. element data;
	element data;
	struct ListNode* link;
} ListNode;

ListNode* insert_first(ListNode* head, int value)
{
	ListNode* p =
		(ListNode*)malloc(sizeof(ListNode));//(1)
	p->data = value;
	// (2)
	p->link = head; //(3)
	head = p; //(4)
	return head;
}
ListNode* insertAtPosition(ListNode* head, int position, element value)
{
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->data = value;
	newNode->link = NULL;

	if (position <= 0) {
		newNode->link = head;
		head = newNode;
		printf("Move along the link: 0\n");
	}
	else {
		ListNode* current = head;
		ListNode* prev = NULL;
		int count = 0;

		while (current != NULL && count < position) {
			prev = current;
			current = current->link;
			count++;
		}

		if (count == position) {
			newNode->link = current;
			if (prev != NULL) {
				prev->link = newNode;
			}
			else {
				head = newNode;
			}
		}
		else {
			if (current != NULL) {
				newNode->link = current->link;
				current->link = newNode;
			}
			else {
				printf("Added at the end of the list\n");
				prev->link = newNode;
			}
		}
		printf("Move along the link: %d\n", count);
	}

	return head;
}


ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head; // (1)
	head = removed->link; // (2)
	free(removed); // (3)
	return head; // (4)
}

ListNode* delete(ListNode* head, ListNode* pre)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link; // (2)
	free(removed); // (3)
	return head; // (4)
}

void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("\n");
	
}
ListNode* deleteAtPosition(ListNode* head, int position)
{
	if (head == NULL) {
		printf("List is empty. Nothing to delete.\n");
		return NULL;
	}

	ListNode* current = head;
	ListNode* prev = NULL;
	int count = 0;

	// 찾고자 하는 위치까지 노드를 이동합니다.
	while (current != NULL && count < position) {
		prev = current;
		current = current->link;
		count++;
	}

	if (count == position) {
		if (prev != NULL) {
			prev->link = current->link;
		}
		else {
			head = current->link;
		}
		free(current);
		printf("Deleted node at position %d. Move along the link: %d\n", position, count);
	}
	else {
		printf("Invalid position. Node not found.\n");
	}

	return head;
}
int main(void)
{
	ListNode* head = NULL;
	
	int select;
	while (1)
	{
		printf("Menu\n( 1 ) Insert\n( 2 ) Delete\n( 3 ) Print\n( 0 ) Exit\nEnter the menu :");
		scanf("%d",&select);
		if (select == 1)
		{
			int num;
			int position;
			printf("Enter the number and position :");
			scanf("%d %d", &num, &position);
			if (head == NULL && position != 0)
			{
				printf("List is empty. Insert at position 0 . . .\n");
				position = 0;
			}

			head = insertAtPosition(head, position, num);
		}
		else if (select == 2)
		{
			int num;
			int position;
			printf("Enter the position to delete:");
			scanf("%d", &position);
			head = deleteAtPosition(head, position);

		}
		else if (select == 3)
		{
			print_list(head);
		}
		else if (select == 0)
		{
			printf("Exit the program ! !");
			break;
		}
		else
			printf("invalid Menu ,please select again\n");
	}
}