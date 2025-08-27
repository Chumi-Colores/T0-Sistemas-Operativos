#include "execute_status.h"

#include <stdio.h>
#include "../../process_group.h"
#include "../../process.h"

void execute_status(char** input, ProcessGroup* process_group)
{
    printf("process_count es: %d\n", process_group->process_count);
    for (size_t i = 0; i < process_group->process_count; i++)
    {
        show_information(&process_group->processes[i]);
    }
}