#include "../minishell.h"

static void	app_redir_out(char *str, t_pipex *p)
{
	int	fd;

	if (!str)
		return ;
	if (access(str, F_OK) != -1 && access(str, W_OK) == -1)
	{
		printf("bad infile\n");
		infile_err();
	}
	p->out_fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);//change to use var in struct so i can close if ctrl C happens same for all redirs
	dup2(p->out_fd, STDOUT_FILENO);
	close(p->out_fd);
}

static void	redir_out(char *str, t_pipex *p)
{
	int	fd;

	if (!str)
		return ;
	if (access(str, F_OK) != -1 && access(str, W_OK) == -1)
	{
		printf("bad infile\n");
		infile_err();
	}
	p->out_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(p->out_fd, STDOUT_FILENO);
	close(p->out_fd);
}

void	do_out_redir(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p)
		return ;
	if (p->next)
		dup2(STDIN_FILENO, p->pipe[1]);//the redirect is the pipe unless others exist and not last cmd
	if (!p->red_out)
		return ;
	while (p->red_out[i] != NULL)
	{
		if (!ft_strncmp(p->red_out[i], "APP:", 4))
			app_redir_out(p->red_out[i] + 4, p);
		else if (!ft_strncmp(p->red_out[i], "STD:", 4))
			redir_out(p->red_out[i] + 4, p);
		i++;
	}
}