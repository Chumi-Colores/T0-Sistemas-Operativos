#include <stdlib.h>
#include "process_group.h"
#include "process.h"

void innit_ProcessGroup(ProcessGroup* process_group) {
    process_group->processes = calloc(100, sizeof(Process));
    process_group->process_count = 0;
}