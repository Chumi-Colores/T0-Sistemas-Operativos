#include "execute_shutdown.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "../../process_group.h"
#include "../../process.h"

void execute_shutdown(char** input, ProcessGroup* process_group)
{
    if (process_group->stop_pid)
    {
        printf("Shutdown already in progress\n");
        return;
    }

    if (process_group->running_processes == 0)
    {
        process_group->stop_pid = -1;
        kill_everyone_inmediately(process_group);
        return;
    }
    

    for (int i = 0; i < process_group->process_count; i++)
    {
        if (kill(process_group->processes[i].pid, 0) == 0)
        {
            kill(process_group->processes[i].pid, SIGINT);
        }
    }

    for (int i = 0; i < process_group->manager_process_count; i++)
    {
        if (kill(process_group->manager_pids[i], 0) == 0)
        {
            kill(process_group->manager_pids[i], SIGINT);
        }
    }

    int pid = fork();

    if (pid == 0) // Child Process
    {
        sleep(10);
        _exit(EXIT_SUCCESS);
    }
    else // Parent Process
    {
        process_group->stop_pid = pid;
        add_manager_process(process_group, pid);
    }
}