typedef struct process {
  int pid;
  int target_time;
  struct process *next;
} Process;

typedef struct queue {
  struct process *head;
  struct process *tail;
  int size;
} Queue;

Queue *create();
void delete(Queue *qu);
int is_empty(Queue *qu); 
void enqueue(Queue *qu, int pid);
int dequeue(Queue *qu);
int peek(Queue *qu);
