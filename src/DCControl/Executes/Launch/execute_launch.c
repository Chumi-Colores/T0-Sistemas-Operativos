#include "execute_launch.h"
#include <unistd.h>
#include <stdio.h>
#include "../../process_group.h"
#include "../../process.h"
#include <time.h>

void execute_launch(char** input, ProcessGroup* process_group)
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
    }
}