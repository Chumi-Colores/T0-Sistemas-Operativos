#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_controller.h"
#include "process_group.h"
#include "Executes/Abort/execute_abort.h"
#include "Executes/Emergency/execute_emergency.h"
#include "Executes/Launch/execute_launch.h"
#include "Executes/Shutdown/execute_shutdown.h"
#include "Executes/Status/execute_status.h"

int process_user_input(char **input, ProcessGroup* process_group)
{
    char* first_word = input[0];

    int continue_playing = 1;

    if (strcmp(first_word, "launch") == 0)
    {
        execute_launch(input, process_group);
    }
    else if (strcmp(first_word, "status") == 0)
    {
        execute_status(input, process_group);
    }
    else if (strcmp(first_word, "abort") == 0)
    {
        execute_abort(input, process_group);
    }
    else if (strcmp(first_word, "shutdown") == 0)
    {
        execute_shutdown(input, process_group);
        continue_playing = 0;
    }
    else if (strcmp(first_word, "emergency") == 0)
    {
        execute_emergency(input, process_group);
        continue_playing = 0;
    }
    else
    {
        printf("Comando no existe: %s \n", first_word);
    }

    return continue_playing;
}
