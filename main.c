#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"
#include "scheduler.h"
#include "switch.h"

int main(void)
{
  FILE *fp = fopen("sample_program.txt", "r");
  char single_line[10];
  char *command, *number;

  if(fp == NULL) {
    printf("Error opening file\n");
    return -1;
  }
  ready_qu = create();
  timed_qu = create();
  io_list[0] = global_clock = 0;

  while(fgets(single_line,10,fp) != NULL) {
    command = strtok(single_line, " \n");
    switch(command[0]) {
      case 'A':
      case 'I':
      case 'K':
        number = strtok(NULL, " \n");
        pid = atoi(number);
        break;
      case 'W':
        number = strtok(NULL, " \n");
        time = atoi(number);
        break;
    }
    done(command[0]);
  }
  delete(ready_qu);
  delete(timed_qu);
  fclose(fp);
  return 0;
}
