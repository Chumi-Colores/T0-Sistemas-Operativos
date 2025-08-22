#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_controller.h"
#include "process.h"
#include "Executes/Abort/execute_abort.h"
#include "Executes/Emergency/execute_emergency.h"
#include "Executes/Launch/execute_launch.h"
#include "Executes/Shutdown/execute_shutdown.h"
#include "Executes/Status/execute_status.h"

void process_user_input(char ** input, Process* processes)
{
    char* first_word = input[0];
    printf("%s\n", first_word);

    if (first_word == "launch")
    {
        execute_launch(input, processes);
    }
    else if (first_word == "status")
    {
        execute_status(input, processes);
    }
    else if (first_word == "abort")
    {
        execute_abort(input, processes);
    }
    else if (first_word == "shutdown")
    {
        execute_shutdown(input, processes);
    }
    else if (first_word == "emergency")
    {
        execute_emergency(input, processes);
    }
    else
    {
        printf("Comando no existe: %s \n", first_word);
    }
}

