#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue_list.h"

typedef struct process process;
struct process {
	char name[40];
};

void print_process(void* data) {
	process* pr = (process*)data;
	printf("%s", pr->name);
}

int main(int argc, char** argv) {
	process* processes[7];
	for (int i = 0; i < 7; i++) {
		processes[i] = (process*)malloc(sizeof(process));
	}
	strcpy(processes[1]->name, "Firefox");
	strcpy(processes[2]->name, "Geany IDE");
	strcpy(processes[3]->name, "Important Calculations");
	strcpy(processes[4]->name, "Elden Ring");
	strcpy(processes[5]->name, "Notion");
	strcpy(processes[6]->name, "Visual Studio Code");

	printf("Created queue_A:\n");
	pqueue* queue_A = NULL;
	insert(&queue_A, processes[1], 5);
	insert(&queue_A, processes[2], 2);
	insert(&queue_A, processes[3], 10);
	print(queue_A, print_process);

	printf("\nPopped one element from queue_A:\n");
	pop(&queue_A);
	print(queue_A, print_process);

	printf("\nPushed one element to queue_A:\n");
	push(&queue_A, processes[1]);
	print(queue_A, print_process);

	printf("\nDeleted by priority 5 from queue_A:\n");
	delete_by_priority(&queue_A, 5);
	print(queue_A, print_process);

	printf("\nInserted one process to queue_A:\n");
	insert(&queue_A, processes[2], 11);
	print(queue_A, print_process);

	printf("\nDeleted by priority 2 from queue_A:\n");
	delete_by_priority(&queue_A, 2);
	print(queue_A, print_process);

	printf("\nDeleted by priority 0 from queue_A:\n");
	delete_by_priority(&queue_A, 0);
	print(queue_A, print_process);

	printf("\nDeleted by priority 11 from queue_A:\n");
	delete_by_priority(&queue_A, 11);
	print(queue_A, print_process);

	printf("\nInserted three processes to queue_A:\n");
	insert(&queue_A, processes[1], 2);
	insert(&queue_A, processes[2], 6);
	insert(&queue_A, processes[3], 0);
	print(queue_A, print_process);

	printf("\nCreated queue_B:\n");
	pqueue* queue_B = NULL;
	insert(&queue_B, processes[4], 6);
	insert(&queue_B, processes[5], 1);
	insert(&queue_B, processes[6], 9);
	print(queue_B, print_process);

	printf("\nCreated queue_C as a merge of queue_A and queue_B:\n");
	pqueue* queue_C = merge_two(queue_A, queue_B);
	print(queue_C, print_process);

	for (int i = 0; i < 7; i++) {
		free(processes[i]);
	}

	return 0;
}