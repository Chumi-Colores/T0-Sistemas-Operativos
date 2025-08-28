
#include <stdio.h>
#include <stdlib.h>
#include "../input_manager/manager.h"
#include "input_controller.h"
#include "process_group.h"
#include "process.h"
#include <signal.h>
#include <sys/wait.h>

ProcessGroup process_group;

void sigchld_handler(int signum) {
	int status;
	int pid;
	Process* process;
	while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		process = get_process(&process_group, pid);
		if (process != NULL)
        {
			update_process(process, status);
		}
	}
}

int main(int argc, char const *argv[])
{
	if (argc < 2)
    {
        printf("No se ha ingresado <time_max>\n");
        exit(EXIT_FAILURE);
	}
    int time_max = atoi(argv[1]);

	initialize_ProcessGroup(&process_group, time_max);
	signal(SIGCHLD, sigchld_handler);

	set_buffer(); // No borrar
	char** input;

	int play = 1;
	while (play)
    {
		input = read_user_input();
		play = process_user_input(input, &process_group);
		free_user_input(input);
	}

	free_all_processes(&process_group);
}
