#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "scheduler.h"

int stop() {
  int stopped_pid;
  if(running_process > 0) {
    stopped_pid = running_process;
    running_process = 0;
    return stopped_pid;
  }
  else {
    return 0;
  }
}

void ready(int pid) {
  enqueue(ready_qu, pid);
}

void sleep(int abs_time) {
  int pid = stop();
  int target_time = global_clock + abs_time;
  enqueue(timed_qu, pid);
  timed_qu->tail->target_time = target_time;
  if(!is_empty(ready_qu)) {
    run_next();
  }
}

void awaken() {
  int pid = dequeue(timed_qu);
  ready(pid);
}

void block() {
  int i = 0;
  int pid = stop();
  while(io_list[i] > 0) {
    i++;
  }
  io_list[i] = pid;
  io_list[i+1] = 0;
  if(!is_empty(ready_qu)) {
    run_next();
  }
}

int run_next() {
  running_process = dequeue(ready_qu);
  return running_process;
}

void tick() {
  global_clock++;
  if(!is_empty(timed_qu)) {
    while(check_awaken()) {
      awaken();
      if(timed_qu->head == NULL) {
        break;
      }
    }
  }
}

int check_awaken() {
  return global_clock == timed_qu->head->target_time;
}

void search_io(int pid) {
  int i = 0;
  while(io_list[i] != pid) {
    i++;
  }
  io_list[i] = 0;
}

int check_io_list(int pid) {
  int i = 0;
  while(io_list[i] != pid) {
    i++;
  }
  return io_list[i];
}

void kill_process(int pid) {
  if(running_process == pid) {
    running_process = 0;
  }
  else if(!is_empty(ready_qu) && ready_qu->head->pid == pid) {
    dequeue(ready_qu);
  }
  else if(!is_empty(timed_qu) && timed_qu->head->pid == pid) {
    dequeue(timed_qu);
  }
  else if(check_io_list(pid)) {
    search_io(pid);
  }
}

void end_program() {
  Process *process = malloc(sizeof(struct process));
  int i;
  if(!is_empty(ready_qu)) {
    process = ready_qu->head;
    do {
      printf("**Ready queue-> ");
      printf("PID: %d\n", process->pid);
      process = process->next;
    } while(process != NULL);
  }
  else {
    printf("**Ready queue is EMPTY!\n");
  }
  if(!is_empty(timed_qu)) {
    process = timed_qu->head;
    do {
      printf("**Timed wait queue-> ");
      printf("PID: %d, Wake-up time: %d\n", process->pid, process->target_time);
      process = process->next;
    } while(process != NULL);
  }
  else {
    printf("**Timed wait queue is EMPTY!\n");
  }
  printf("**I/O waiting list: ");
  for(i=0; i<10; i++) {
    printf("%d ", io_list[i]);
  }
  puts("");
  printf("**Currently running process is %d\n", running_process);
  printf("**Timer count: %d\n", global_clock);
}
