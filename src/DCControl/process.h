#pragma once

typedef struct process
{
    int pid;
    char* name;
    int exit_code;
    int signal_value;
} Process;
