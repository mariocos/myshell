#include "../minishell.h"

/*
the parent proccess should be called with a t_pipex struct wich allows it to execute a comand
*/
void	pipe_error(void)
{
	printf("\n\na critical error has ocurred when creating a pipe\n\n");
	perror("pipe");
	exit(EXIT_FAILURE);
}

void	fork_error(void)
{
	printf("a critical error has occured trying to fork\n");
	perror("fork");
	exit(EXIT_FAILURE);
}

void	close_fds(int *fds)
{
	close(fds[0]);
	close(fds[1]);
}
/*
get_fd functions get the fd for each output and input, this is done like in bash and is only
redirected inside the child
*/
void	spawn_child(t_pipex *p)
{
	pid_t	pid;

	if (!p)//this should be exit so we dont get double forks
		return ;
	if (pipe(p->pipe) < 0)
		pipe_error();
	pid = fork();
	if (pid < 0)
		fork_error();
	if (pid == 0)
		child_process_new(p);
	dup2(p->pipe[0], STDIN_FILENO);
	close_fds(p->pipe);	
}

	//M - if child was bad stop piping - missing implementation
	//H - Isn't exit_failure in child enough?
void	process_handler(t_pipex *p)
{
	pid_t p_id;
	
	while(p != NULL)
	{
		p->last_child = (p->next == NULL);
		spawn_child(p);
		p = p->next;
	}
	p_id = 1;
	while (p_id > 0)
		p_id = wait(NULL);
}
