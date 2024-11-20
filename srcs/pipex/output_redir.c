#include "../minishell.h"

void	do_out_redir(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p || !p->red_out)
		return ;
	while (p->red_out[i] != NULL)
	{
		if (!ft_strncmp(p->red_out[i], "APP:", 4))
			app_redir_out(p->red_out[i] + 4);
		else if (!ft_strncmp(p->red_out[i], "STD:", 4))
			redir_out(p->red_out[i] + 4);
		i++;
	}
}

void	app_redir_out(char *str)
{
	int	fd;

	if (!str)
		return ;
	if (access(str, F_OK) != -1 && access(str, W_OK) == -1)
	{
		printf("bad infile\n");
		infile_err();
	}
	fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_out(char *str)
{
	int	fd;

	if (!str)
		return ;
	if (access(str, F_OK) != -1 && access(str, W_OK) == -1)
	{
		printf("bad infile\n");
		infile_err();
	}
	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}