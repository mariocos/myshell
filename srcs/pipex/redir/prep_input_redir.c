#include "../../minishell.h"

void	read_into_pipe(char *eof, t_pipex *p)
{
	char *str;

	close(p->doc_pipe[0]);//this line breaks heredocs and idk why
	while (1)
	{
		write(1, "pipe into doc>", 14);
		str = get_next_line(0);//this might leak on ctrl-c
		if (!ft_strncmp(str, eof, ft_strlen(eof)))//might want to change because this might also catch if you write more than just the finissher
		{
			free(str);
			break ;
		}
		write(p->doc_pipe[1], str, ft_strlen(str));
	}
	close(p->doc_pipe[1]);
	exit(0);
}


static void	do_here_doc(char *str, t_pipex *p)
{
	int	pid;//change to struct???

	if (pipe(p->doc_pipe) < 0)
		printf("critical pipe erro\n");//handle error
	pid = fork();
	if (pid < 0)
	{
		close_fds(p->doc_pipe);
		printf("crit error on fork\n");
		return ;
	}
	if (pid == 0)
		read_into_pipe(str, p);
	close(p->doc_pipe[1]);
	ft_waitpid(pid);
}

static void	input_redir(char *str, t_pipex *p)//to be tested but pretty sure it still works
{
	//check file perms
	if (access(str, F_OK) == -1 || access(str, R_OK) == -1)
	{
		printf("bad infile dude\n");
//		infile_error();//TODO:mi
	}
	p->in_fd = open(str, O_RDONLY);
}

void	if_close(int fd)
{
	if (fd > 2)
		close (fd);
}

void	prep_input_redir(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p)
		return ;
	while (p)
	{
		i = 0;
		while (p->red_in && p->red_in[i])
		{
			if (!ft_strncmp(p->red_in[i], "STD:", 4))//change has_doc to zero and close doc pipe
			{
				if (p->has_doc)
					close_fds(p->doc_pipe);
				p->has_doc = 0;
				if_close(p->in_fd);
				input_redir(p->red_in[i] + 4, p);
			}
			else if (!ft_strncmp(p->red_in[i], "APP:", 4))
			{			
				if_close(p->in_fd);
				if (p->has_doc)
					close_fds(p->doc_pipe);
				p->has_doc = 1;
				do_here_doc(p->red_in[i] + 4, p);
			} 
			i++;
		}
		p = p->next;
	}
}
