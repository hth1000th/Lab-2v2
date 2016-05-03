#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* create() {
  Queue *qu = malloc(sizeof(struct queue));
  qu->head = NULL;
  qu->tail = NULL;
  qu->size = 0;
  return qu;
}

void delete(Queue *qu) {
  while(!is_empty(qu)) {
    dequeue(qu);
  }
  free(qu);
}

int is_empty(Queue *qu) {
  return qu->size == 0;
}

void enqueue(Queue *qu, int pid) {
  Process *new_proc = malloc(sizeof(struct process));
  new_proc->pid = pid;
  new_proc->next = NULL;
  if(is_empty(qu)) {
    qu->head = new_proc;
    qu->tail = new_proc;
  }
  else {
    qu->tail->next = new_proc;
    qu->tail = new_proc;
  }
  qu->size++;
}

int dequeue(Queue *qu) {
  int pid;
  if(is_empty(qu)) {
    printf("Queue is empty.\n");
    exit(-1);
  }
  pid = qu->head->pid;
  qu->head = qu->head->next;
  if(qu->head == NULL) {
    qu->tail = NULL;
  }
  qu->size--;
  return pid;
}

int peek(Queue *qu) {
  if(is_empty(qu)) {
    printf("Queue is empty.\n");
    return -1;
  }
  else {
    return qu->head->pid;
  }
}
