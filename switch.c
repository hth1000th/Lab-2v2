#include <stdio.h>
#include "queue.h"
#include "scheduler.h"
#include "switch.h"

void done(int command) {
  int proc_id;
  switch(command) {
    case 'A':
      ready(pid);
      break;
    case 'T':
      proc_id = stop();
      if(proc_id != 0) {
        ready(proc_id);
      }
      tick();
      run_next();
      break;
    case 'S':
      block();
      break;
    case 'I':
      search_io(pid);
      ready(pid);
      break;
    case 'W':
      sleep(time);
      break;
    case 'K':
      kill_process(pid);
      break;
    case 'E':
      end_program();
      break;
  }
}
