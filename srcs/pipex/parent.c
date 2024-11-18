#include "../minishel.h"

/*
the parent proccess should be called with a t_pipex struct wich allows it to execute a comand
*/
void	pipe_error(void)
{
	printf("\n\na critical error has ocurred when creating a pipe\n\n");
}

void	fork_error(void)
{
	printf("a critical error has occured trying to fork\n");
}
/*
get_fd functions get the fd for each output and input, this is done like in bash and is only
redirected inside the child
*/
void	ft_parent_process(t_pipex *p)
{
	int	pid;

	if (!p)
		return ;
	//creating pipe for current comand,
	if (pipe(p->pipe) < 0)
		pipe_error();
	pid = fork();
	if (pid < 0)
		fork_error();
	if (pid == 0)//missing check for first and last child to not dup2 the fileno_stdin and out with the pipe
		child_process(p);
	dup2(p->pipe[0], STDIN_FILENO);
	close_fds(p->pipe);//missing implementation	
}

void	grandparent_process(t_pipex *p)
{
	//while pipe to do do pipe
	//if child was bad stop piping


	//wait for all childs to end
//	wait();
}
