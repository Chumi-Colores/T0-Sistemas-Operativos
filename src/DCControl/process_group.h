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

Process* get_process(ProcessGroup* process_group, int pid);