#include "execute_launch.h"
#include <unistd.h>
#include <stdio.h>
#include "../../process_group.h"
#include "../../process.h"
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

void execute_launch(char** input, ProcessGroup* process_group, int time_max)
{
    int pid = fork();
    if (pid == 0) // Child process
    {
        char* executable = input[1];
        char** args = &input[1];
        if (execvp(executable, args) == -1)
        {
            printf("Executable: %s failed\n", executable);
            _exit(1);
        }
    } 
    else // Parent process
    {
        add_process(process_group, input, pid);
        if (time_max > 0){
            int time_max_monitor_pid = fork();
            if (time_max_monitor_pid == 0) // Child process to monitor time_max
            {
                    sleep(time_max);
                    if (kill(pid, SIGTERM) == 0) { // Vemos si el hijo sigue vivo y le pedimos amablemente que se suicide
                        sleep(5);
                        if (kill(pid, 0) == 0) // Si sigue vivo, le pedimos por las malas
                        {
                            printf("Tiempo límite excedido, matando al proceso hijo %s...\n", get_process(process_group, pid)->name);
                            kill(pid, SIGKILL);
                        }
                    }
                exit(0);
            }
        }
    }
}