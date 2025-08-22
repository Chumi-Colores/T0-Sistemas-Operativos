
#include <stdio.h>
#include <stdlib.h>
#include "../input_manager/manager.h"
#include "input_controller.h"
#include "process.h"

int main(int argc, char const *argv[])
{
  set_buffer(); // No borrar
  char** input;

  Process* processes = calloc(100, sizeof(Process));

  while (1){
    input = read_user_input();
    process_user_input(input, processes);
    free_user_input(input);
  }
}
