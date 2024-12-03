#include "../minishell.h"

/*
this file need to be changed, input redirs are setup before the fork and dup2d after the fork.
*/

void	do_input_redir(t_pipex *p)//to be changed to just check if in_fd is 0, if not dup with in_fd.
{
	int	i;

	i = 0;
	if (!p)
		return ;
	if (p->previous)
	{
		dup2(p->previous->pipe[0], STDIN_FILENO);
		close(p->previous->pipe[0]);
	}
	if (!p->red_in)
		return ;
	else
	{
	//	printf("redirectin in\n");
		if (p->has_doc)
		{
			dup2(p->doc_pipe[0], STDIN_FILENO);
			close(p->doc_pipe[0]);

		}
		else
		{
			dup2(p->in_fd, STDIN_FILENO);
			close(p->in_fd);
		}
	}
}
