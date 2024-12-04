#include "../../minishell.h"

void	do_out_redir(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p)
		return ;
	if (p->next != NULL)
	{
		dup2(p->pipe[1], STDOUT_FILENO);
		close(p->pipe[1]);
	}
	if (!p->red_out)
		return ;
	dup2(p->out_fd, STDOUT_FILENO);
}