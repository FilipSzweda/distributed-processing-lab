#include <stdio.h>
#include <stdlib.h>
#include "priority_queue_list.h"

void push(pqueue** head, void* data) {
	/*if (!*head) {
		*head = (pqueue*)malloc(sizeof(pqueue));
		(*head)->data = data;
		(*head)->priority = 0;
		(*head)->next = NULL;
		(*head)->prev = NULL;
	}
	else {
		pqueue* tail;
		for (tail = *head; tail->next != NULL; tail = tail->next);
		pqueue* newElement = (pqueue*)malloc(sizeof(pqueue));
		newElement->data = data;
		newElement->priority = tail->priority - 1;
		newElement->next = NULL;
		newElement->prev = tail;
		tail->next = newElement;
	}*/
	insert(&*head, data, 0);
}

void pop(pqueue** head) {
	if (*head) {
		if ((*head)->next) {
			*head = (*head)->next;
			free((*head)->prev);
			(*head)->prev = NULL;
		}
		else {
			free(*head);
			*head = NULL;
		}
	}
}

void print(pqueue* head, void (*print_data)(void*)) {
	if (head) {
		for (pqueue* element = head; element != NULL; element = element->next) {
			printf("%d: ", element->priority);
			print_data(element->data);
			printf("\n");
		}
	}
}

void insert(pqueue** head, void* data, int priority) {
	if (!*head) {
		*head = (pqueue*)malloc(sizeof(pqueue));
		(*head)->data = data;
		(*head)->priority = priority;
		(*head)->next = NULL;
		(*head)->prev = NULL;
	}
	else {
		pqueue* element;
		for (element = *head; element->next != NULL && element->priority > priority; element = element->next);
		pqueue* newElement = (pqueue*)malloc(sizeof(pqueue));
		newElement->data = data;
		newElement->priority = priority;
		if (element == *head) {
			if (element->priority < priority) {
				newElement->next = *head;
				newElement->prev = NULL;
				(*head)->prev = newElement;
				*head = newElement;
			}
			else {
				newElement->next = (*head)->next;
				newElement->prev = *head;
				if ((*head)->next) (*head)->next->prev = newElement;
				(*head)->next = newElement;
			}
		}
		else if (element->next == NULL) {
			if (element->priority < priority) {
				newElement->next = element;
				newElement->prev = element->prev;
				element->prev->next = newElement;
				element->prev = newElement;
			}
			else {
				newElement->next = NULL;
				newElement->prev = element;
				element->next = newElement;
			}
		}
		else {
			newElement->next = element->next;
			newElement->prev = element;
			element->next->prev = newElement;
			element->next = newElement;
		}
	}
}

void delete_by_priority(pqueue** head, int priority) {
	pqueue* nextElement;
	for (pqueue* element = *head; element != NULL; element = nextElement) {
		nextElement = element->next;
		if (element->priority == priority) {
			if (element == *head) {
				pop(&*head);
			}
			else if (element->next == NULL) {
				element->prev->next = NULL;
				free(element);
			}
			else {
				element->next->prev = element->prev;
				element->prev->next = element->next;
				free(element);
			}
		}
	}
}

pqueue* merge_two(pqueue* queue_A, pqueue* queue_B) {
	pqueue* queue_C = NULL;
	for (pqueue* element = queue_A; element != NULL; element = element->next) {
		insert(&queue_C, element->data, element->priority);
	}
	for (pqueue* element = queue_B; element != NULL; element = element->next) {
		insert(&queue_C, element->data, element->priority);
	}
	return queue_C;
}