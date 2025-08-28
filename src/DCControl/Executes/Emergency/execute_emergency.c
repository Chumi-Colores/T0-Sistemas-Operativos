#include "execute_emergency.h"

#include <stdio.h>
#include "../../process_group.h"
#include "../../process.h"

void execute_emergency(char **input, ProcessGroup* process_group)
{
    printf("¡Emergencia!\n");
    printf("DCControl finalizado.\n");
    kill_everyone_inmediately(process_group);
}