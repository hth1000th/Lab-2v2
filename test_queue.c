#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "queue.h"
#include <test_queue.h>

Queue *qu;
int main(void) {

  test_create();
  test_is_empty();
  test_enqueue();
  test_dequeue();
  test_peek();
  delete(qu);

  puts("testing complete");
  return 0;
}

void test_create() {
  qu = create();

  puts("testing Queue create()");
  assert(qu->head == NULL && qu->tail == NULL && qu->size == 0);
}

void test_is_empty() {
  puts("testing int is_empty(Queue qu)");
  qu->size = 1;
  assert(is_empty(qu) == 0);
  qu->size = -1;
  assert(is_empty(qu) == 0);
  qu->size = 0;
  assert(is_empty(qu) == 1);
}

void test_enqueue() {
  puts("testing void enqueue(Queue qu, int pid)");
  enqueue(qu, 123);
  assert(qu->tail->pid == 123 && qu->size == 1);
  enqueue(qu, 000);
  assert(qu->tail->pid == 0 && qu->size == 2);
  enqueue(qu, 9);
  assert(qu->tail->pid == 9 && qu->size == 3);
  enqueue(qu, -10);
  assert(qu->tail->pid == -10 && qu->size == 4);
}

void test_dequeue() {
  puts("testing int dequeue(Queue qu)");
  assert(dequeue(qu) == 123);
  assert(dequeue(qu) == 0);
  assert(dequeue(qu) == 9);
  assert(dequeue(qu) == -10);
}

void test_peek() {
  puts("testing int peek(Queue qu)");
  assert(peek(qu) == -1);
  enqueue(qu, 456);
  assert(peek(qu) == 456);
  enqueue(qu, 789);
  dequeue(qu);
  assert(peek(qu) == 789);
}
