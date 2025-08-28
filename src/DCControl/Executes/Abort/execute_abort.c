#include "execute_abort.h"

#include <stdio.h>
#include "../../process_group.h"
#include "../../process.h"

void execute_abort(char** input, ProcessGroup* process_group)
{
    char* input_time = input[1];
    int abort_time = 0;
    if (input_time != NULL) {
        abort_time = atoi(input_time);
    } else{
        abort_time = 3;
    }

    if (are_any_process_running(process_group)){
        int aborting_process_pid = fork();
        if (aborting_process_pid == 0){
            // Proceso hijo
            int current_process_count = process_group->process_count;
            sleep(abort_time);
            abort_processes_in_range(process_group, current_process_count);
            printf("\n"); fflush(stdout);
            exit(0);
        }
    }
    else {
        printf("No hay procesos en ejecución. Abort no se puede ejecutar.\n");
    }

}