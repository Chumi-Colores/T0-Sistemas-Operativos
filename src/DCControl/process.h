#pragma once
#include <time.h>

typedef struct process
{
    int pid;
    char* name;
    time_t start_time;
    time_t end_time;
    int exit_code;
    int signal_value;
} Process;

void initialize_Process(Process* process, char** input, int pid);

void show_information(Process* process);

void update_process(Process* process, int status);