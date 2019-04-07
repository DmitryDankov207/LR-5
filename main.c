#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101

typedef int T;

typedef struct node {
	T value;
	struct node *next;
} Node_s;

void push(Node_s **head, T value) {
	Node_s *tmp = (Node_s*)malloc(sizeof(Node_s));
	if (tmp == NULL)
		exit(STACK_OVERFLOW);
	tmp->next = *head;
	tmp->value = value;
	*head = tmp;
}

T pop(Node_s **head) {
	Node_s *out;
	T value;
	if (*head == NULL)
		exit(STACK_UNDERFLOW);
	value = (*head)->value;
	out = *head;
	*head = (*head)->next;
	free(out);
	return value;
}

T peek(const Node_s* head) {
	if (head == NULL)
		exit(STACK_UNDERFLOW);
	return head->value;
}

void insert(Node_s **head, T value_1) {
	if (*head) {
		T value_2 = peek(*head);
		if (value_1 > value_2) {
			pop(head);
			insert(head, value_1);
			push(head, value_2);
		}
		else if (value_1 == value_2);
		else
			push(head, value_1);
	}
	else
		push(head, value_1);
}

void sort(Node_s ** head) {
	if (*head) {
		T value = pop(head);
		sort(head);
		insert(head, value);
	}
}

void generateStack(Node_s **head, size_t size) {
	for (size_t i = 0; i < size; i++)
		push(head, rand() % 100);
}

void printStack(const Node_s *head) {
	while (head) {
		printf_s("%d ", head->value);
		head = head->next;
	}
}

void makeSortedStack(Node_s **head, size_t size) {
	generateStack(head, size);
	printf_s("\nunsorted:\n");
	printStack(*head);
	sort(head);
	printf_s("\nsorted:\n");
	printStack(*head);
}

void connectStacks(const Node_s *head1, const Node_s *head2, Node_s **out) {
	while (head1 || head2) {
		if (head1) {
			push(out, head1->value);
			head1 = head1->next;
		}
		if (head2) {
			push(out, head2->value);
			head2 = head2->next;
		}
	}
	sort(out);
}

void makeTask() {
	Node_s *head1 = NULL, *head2 = NULL, *head3 = NULL;
	size_t size1, size2;
	scanf_s("%d", &size1);
	scanf_s("%d", &size2);
	makeSortedStack(&head1, size1);
	printf_s("\n");
	makeSortedStack(&head2, size2);
	connectStacks(head1, head2, &head3);
	printf_s("\n\nresult:\n");
	printStack(head3);
	free(head1);
	free(head2);
	free(head3);
}

int main() {
	makeTask();
	_getch();
	return 0;
}