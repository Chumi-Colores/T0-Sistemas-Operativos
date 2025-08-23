
#include <stdio.h>
#include <stdlib.h>
#include "../input_manager/manager.h"
#include "input_controller.h"
#include "process_group.h"
#include "process.h"
#include <signal.h>

ProcessGroup process_group;

void sigchld_handler(int signum) {
  int status;
  int pid;
  Process* process;
  while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
  {
    process = get_process(&process_group, pid);
    update_process(process, status);
  }
}

int main(int argc, char const *argv[])
{
  initialize_ProcessGroup(&process_group);
  signal(SIGCHLD, sigchld_handler);

  set_buffer(); // No borrar
  char** input;

  while (1) {
    input = read_user_input();
    process_user_input(input, &process_group);
    free_user_input(input);
  }
}
