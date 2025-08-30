#include "execute_abort.h"
#include <unistd.h>
#include <stdio.h>
#include "../../process_group.h"
#include "../../process.h"

void execute_abort(char** input, ProcessGroup* process_group)
{
    if (process_group->stop_pid)
    {
        printf("Shutdown in progress, abort cancelled\n");
        return;
    }
    char* input_time = input[1];

    if (input_time == NULL) 
    {
        printf("No se ha ingresado <abort_time>\n");
        return;
    }

    int abort_time = atoi(input_time);

    if (process_group->running_processes == 0)
    {
        printf("No hay procesos en ejecución. Abort no se puede ejecutar.\n");
        return;
    }

    int aborting_process_pid = fork();
    if (aborting_process_pid == 0) // Child process
    {
        int current_process_count = process_group->process_count;
        sleep(abort_time);
        abort_processes_in_range(process_group, current_process_count);
        _exit(EXIT_SUCCESS);
    }
    else // Parent Process
    {
        add_manager_process(process_group, aborting_process_pid);
    }
}