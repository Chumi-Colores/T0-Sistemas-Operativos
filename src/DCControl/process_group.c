#include <stdlib.h>
#include "process_group.h"
#include "process.h"
#include <stdio.h>
#include <signal.h>

void initialize_ProcessGroup(ProcessGroup* process_group) {
    process_group->max_processes = 10;
    process_group->processes = malloc(process_group->max_processes * sizeof(Process));
    process_group->process_count = 0;
}

void add_process(ProcessGroup* process_group, char** input, int pid)
{
    if (process_group->process_count == process_group->max_processes)
    {
        increase_process_capacity(process_group);
    }
    initialize_Process(&process_group->processes[process_group->process_count], input, pid);
    process_group->process_count += 1;
}

void increase_process_capacity(ProcessGroup* process_group)
{
    process_group->max_processes *= 2;
    process_group->processes = realloc(process_group->processes, process_group->max_processes * sizeof(Process));
}

int are_any_process_running(ProcessGroup* process_group)
{
    for (int i = 0; i < process_group->process_count; i++)
    {
        if (process_group->processes[i].end_time == 0)
        {
            return 1;
        }
    }
    return 0;
}

void kill_processes_range(ProcessGroup* process_group, int end){
    for (int i = 0; i < end; i++)
    {
        if (process_group->processes[i].end_time == 0)
        {
            kill(process_group->processes[i].pid, SIGTERM);
            printf("%d %s %lld %d %d\n",
                   process_group->processes[i].pid,
                   process_group->processes[i].name,
                   (long long) (time(NULL) - process_group->processes[i].start_time),
                   process_group->processes[i].exit_code,
                   process_group->processes[i].signal_value);
        }
    }
}

Process* get_process(ProcessGroup* process_group, int pid)
{
    for (int i = 0; i < process_group->process_count; i++)
    {
        if (process_group->processes[i].pid == pid)
        {
            return &process_group->processes[i];
        }
    }
    return NULL;
}

