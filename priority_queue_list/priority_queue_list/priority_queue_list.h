typedef struct pqueue pqueue;
struct pqueue {
	int priority;
	void* data;
	pqueue* next;
	pqueue* prev;
};

void push(pqueue** phead, void* data);
void pop(pqueue** phead);
void print(pqueue* head, void (*print_data)(void*));

void insert(pqueue** phead, void* data, int priority);
void delete_by_priority(pqueue** phead, int priority);

pqueue* merge_two(pqueue* queue_A, pqueue* queue_B);