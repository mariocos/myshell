#include "../minishell.h"

void	child_process_new(t_pipex	*p)
{
	if (!p)
		return ;
	if (!p->last_child)
		dup2(p->pipe[1], STDOUT_FILENO);
	
	//do redirections!
	do_input_redir(p);

	close_fds(p->pipe);
	execve(p->path, p->cmd, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}