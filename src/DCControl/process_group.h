#pragma once
#include <stdlib.h>
#include "process.h"


typedef struct process_group
{
    Process* processes;
    int process_count;
} ProcessGroup;


void innit_ProcessGroup(ProcessGroup* process_group);