
#include <stdio.h>
#include <stdlib.h>
#include "../input_manager/manager.h"
#include "input_controller.h"
#include "process_group.h"

int main(int argc, char const *argv[])
{
  set_buffer(); // No borrar
  char** input;

  ProcessGroup process_group;
  innit_ProcessGroup(&process_group);

  while (1) {
    input = read_user_input();
    process_user_input(input, &process_group);
    free_user_input(input);
  }
}
