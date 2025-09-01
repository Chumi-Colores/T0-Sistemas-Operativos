
#include <stdio.h>
#include <stdlib.h>
#include "../input_manager/manager.h"
#include "input_controller.h"
#include "process_group.h"
#include "process.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

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
			process_group.running_processes -= 1;
		}
		else
		{
			process_group.running_manager_processes -= 1;

			if (pid == process_group.stop_pid)
			{
				kill_everyone_inmediately(&process_group);
        		printf("\n"); fflush(stdout);
			}
		}

		if (process_group.stop_pid && process_group.running_processes == 0 && process_group.running_manager_processes == 0)
		{
			free_ProcessGroup(&process_group);
			exit(EXIT_SUCCESS);
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

	while (!process_group.stop_pid || process_group.running_processes > 0 || process_group.running_manager_processes > 0)
    {
		input = read_user_input();
		process_user_input(input, &process_group);
		free_user_input(input);
	}
}
