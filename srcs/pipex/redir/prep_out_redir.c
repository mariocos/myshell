#include "../../minishell.h"


static int	app_redir_out(char *str, t_pipex *p)
{
	if (!str)
		return (0);
	if (access(str, F_OK) != -1 && access(str, W_OK) == -1)
	{
		printf("bad infile\n");//better message
		return (-1);
	}
	p->out_fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (1);
}

static int	redir_out(char *str, t_pipex *p)
{
	if (!str)
		return (0);
	if (access(str, F_OK) != -1 && access(str, W_OK) == -1)
	{
		printf("bad outfile :(\n");//better message to be done 
		return (-1);
	}
	p->out_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (1);
}


int	prep_output_redir(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p)
		return (0);
	while (p)
	{
		i = 0;
		while (p->red_out && p->red_out[i])
		{
			if (!ft_strncmp(p->red_out[i], "STD:", 4))
			{
				if_close(p->out_fd);
				if (redir_out(p->red_out[i] + 4, p) < 0)
					return (-1);
			}
			else if (!ft_strncmp(p->red_out[i], "APP:", 4))
			{			
				if_close(p->in_fd);
				if (app_redir_out(p->red_in[i] + 4, p) < 0)
					return (-1);
			} 
			i++;
		}
		p = p->next;
	}
	return (1);
}
