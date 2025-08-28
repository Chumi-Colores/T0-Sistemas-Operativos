#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "process.h"


void initialize_Process(Process* process, char** input, int pid)
{
    process->pid = pid;
    process->name = malloc(strlen(input[1]) + 1);
    strcpy(process->name, input[1]);
    process->start_time = time(NULL);
    process->exit_code = -1;
    process->signal_value = -1;
}


void show_information(Process* process){
    // printf("Process ID: %i\n", process->pid);
    // printf("Name: %s\n", process->name);
    // if (process->end_time == 0){
    //     printf("Execution time: %lld seconds\n", (long long) (time(NULL) - process->start_time));
    // } else {
    //     printf("Execution time: %lld seconds\n", (long long) (process->end_time - process->start_time));
    // }
    // printf("Exit code: %i\n", process->exit_code);
    // printf("Signal value: %i\n", process->signal_value);
    // printf("\n");

    // PARA GONZALO: Preferí hacerlo en una sola línea para mantener formato con otras partes de la tarea
    long long int execution_time = (process->end_time == 0) ? (long long) (time(NULL) - process->start_time) : (long long) (process->end_time - process->start_time);

    printf("%i %s %lld %d %d\n",
           process->pid,
           process->name,
           execution_time,
           process->exit_code,
           process->signal_value);
}


void update_process(Process* process, int status)
{
    process->end_time = time(NULL);

    if (WIFEXITED(status))
    {
        process->exit_code = WEXITSTATUS(status);
    } 
    else if (WIFSIGNALED(status))
    {
        process->signal_value = WTERMSIG(status);
    }
}