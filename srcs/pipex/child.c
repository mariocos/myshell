#include "../minishel.h"

void	child_proccess(t_pipex	*p)
{
	//do redirections!
	do_input_redir(p);

	//close pipe
}

void	do_input_redir(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p || !p->red_in)
		return ;
	while (p->red_in[i] != NULL)
	{
		if (!ft_strncmp(p->red_in[i], "APP:", 4))
			do_here_doc(p->red_in[i] + 4);
		else if (!ft_strncmp(p->red_in[i], "STD:", 4))
			input_redir(p->red_in[i]);
	}
}

void	do_here_doc(char *str)
{
	//clean file

	//read into file with gnl'

	//dupe stdin with tempfile_fd
}