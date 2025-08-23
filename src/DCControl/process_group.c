#include <stdlib.h>
#include "process_group.h"
#include "process.h"
#include <stdio.h>

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

