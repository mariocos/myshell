#include "../../minishell.h"


static void	app_redir_out(char *str, t_pipex *p)
{
	if (!str)
		return ;
	if (access(str, F_OK) != -1 && access(str, W_OK) == -1)
	{
		printf("bad infile\n");//error not handled
	}
	p->out_fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

static void	redir_out(char *str, t_pipex *p)
{
	if (!str)
		return ;
	if (access(str, F_OK) != -1 && access(str, W_OK) == -1)
	{
		printf("bad outfile :(\n");//error not handled
	}
	p->out_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}


void	prep_output_redir(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p)
		return ;
	while (p)
	{
		i = 0;
		while (p->red_out && p->red_out[i])
		{
			if (!ft_strncmp(p->red_out[i], "STD:", 4))
			{
				if_close(p->out_fd);
				redir_out(p->red_out[i] + 4, p);
			}
			else if (!ft_strncmp(p->red_out[i], "APP:", 4))
			{			
				if_close(p->in_fd);
				app_redir_out(p->red_in[i] + 4, p);
			} 
			i++;
		}
		p = p->next;
	}
}
