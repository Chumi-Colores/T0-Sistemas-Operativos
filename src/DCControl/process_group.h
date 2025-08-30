#pragma once

#include <stdlib.h>
#include "process.h"


typedef struct process_group
{
    Process* processes;
    int process_count;
    int max_processes;
    int running_processes;

    int time_max;

    int* manager_pids;
    int manager_process_count;
    int max_manager_processes;
    int running_manager_processes;
    int stop_pid;
} ProcessGroup;


void initialize_ProcessGroup(ProcessGroup* process_group, int time_max);

void add_process(ProcessGroup* process_group, char** input, int pid);

void add_manager_process(ProcessGroup* process_group, int pid);

void increase_manager_process_capacity(ProcessGroup* process_group);

void increase_process_capacity(ProcessGroup* process_group);

void abort_processes_in_range(ProcessGroup* process_group, int end);

void kill_everyone_inmediately(ProcessGroup* process_group);

void free_ProcessGroup(ProcessGroup* process_group);

Process* get_process(ProcessGroup* process_group, int pid);