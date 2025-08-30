#include "execute_launch.h"
#include <unistd.h>
#include <stdio.h>
#include "../../process_group.h"
#include "../../process.h"
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

void execute_launch(char** input, ProcessGroup* process_group)
{
    int pid = fork();
    if (pid == 0) // Child process
    {
        char* executable = input[1];
        char** args = &input[1];
        if (execvp(executable, args) == -1)
        {
            printf("Executable: %s failed\n", executable);
            _exit(EXIT_FAILURE);
        }
        _exit(EXIT_SUCCESS);
    } 
    else // Parent process
    {
        add_process(process_group, input, pid);

        int time_max_monitor_pid = fork();
        if (time_max_monitor_pid == 0) // Child process to monitor time_max
        {
            sleep(process_group->time_max);
            if (kill(pid, SIGTERM) == 0) // Vemos si el hijo sigue vivo y le pedimos amablemente que se suicide
            {
                sleep(5);
                if (kill(pid, 0) == 0) // Si sigue vivo, le pedimos por las malas
                {
                    printf("Tiempo límite excedido, matando al proceso hijo %s...\n", get_process(process_group, pid)->name);
                    kill(pid, SIGKILL);
                }
            }
            _exit(EXIT_SUCCESS);
        }
        else // Parent process
        {
            add_manager_process(process_group, time_max_monitor_pid);
        }
        
    }
}