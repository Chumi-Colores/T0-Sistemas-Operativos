#pragma once
#include <stdlib.h>
#include "process.h"


typedef struct process_group
{
    Process* processes;
    int process_count;
    int max_processes;
} ProcessGroup;


void initialize_ProcessGroup(ProcessGroup* process_group);

void add_process(ProcessGroup* process_group, char** input, int pid);

void increase_process_capacity(ProcessGroup* process_group);

int are_any_process_running(ProcessGroup* process_group);

void abort_processes_in_range(ProcessGroup* process_group, int end);

void kill_everyone_inmediately(ProcessGroup* process_group);

void free_all_processes(ProcessGroup* process_group);

Process* get_process(ProcessGroup* process_group, int pid);