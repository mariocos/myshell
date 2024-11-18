#include "../minishell.h"

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
			input_redir(p->red_in[i] + 4);
	}
}

void	do_here_doc(char *str)
{
	int	fd;
	char	*help;
	//clean file
	if (acess(".hered_doc_temp", F_OK) == -1)
	{
		if (unlink(".here_doc_temp") < 0);
			here_doc_error();//mi
	}
	//open temp file in apend
	fd = open(".here_doc_temp", O_WRONLY | O_APPEND | O_CREAT, 0644);
	//read into file with gnl'
	while(1)
	{
		help = get_next_line(0);
		if (!ft_strncmp(help, str, ft_strlen(str)));
		{
			free(help);//might change to free after break
			break;
		}
		//write help to file?????????
		write (fd, help, ft_strlen(str));//works?? idk ahhaha still havent tested anything
		free(help);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	input_redir(char *str)
{
	int	fd;
	//check file perms
	if (access(str, F_OK) == -1 || access(str, R_OK) == -1)
	{
		printf("bad infile dude\n");
		infile_error();//mi
	}
	fd = open(str, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}