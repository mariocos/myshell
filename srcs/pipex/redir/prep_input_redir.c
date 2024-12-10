/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_input_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:43:47 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/10 14:50:43 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	read_into_pipe(char *eof, t_pipex *p)
{
	char *str;

	close(p->doc_pipe[0]);
	while (1)
	{
		write(1, "pipe into doc>", 14);
		str = get_next_line(0);
		if (str == NULL)
		{
			write(1, "\n", 1);
			free (str);
			exit (144);
		}
		if (!ft_strncmp(str, eof, ft_strlen(eof)))
		{
			free(str);
			break ;
		}
		write(p->doc_pipe[1], str, ft_strlen(str));
	}
	close(p->doc_pipe[1]);
	exit(0);
}

static int	do_here_doc(char *str, t_pipex *p)
{
	int	pid;

	if (pipe(p->doc_pipe) < 0)
		return (here_pipe_error());
	pid = fork();
	if (pid < 0)
	{
		close_fds(p->doc_pipe);
		printf("crit error on fork\n");
		return (-1);
	}
	if (pid == 0)
	{
		setup_child_process_signal_handlers();
		read_into_pipe(str, p);
	}
	setup_signal_handlers_heredoc();
	close(p->doc_pipe[1]);
	ft_waitpid(pid);
	setup_signal_handlers();
	if (p->has_doc && mini_call()->exit_status != 0)
		return (-1);
	return (1);
}

static int	input_redir(char *str, t_pipex *p)
{
	if (access(str, F_OK) == -1 || access(str, R_OK) == -1)
	{
		return (-1);
	}
	p->in_fd = open(str, O_RDONLY);
	return (1);
}

void	if_close(int fd)
{
	if (fd > 2)
		close (fd);
}

int	prep_input_redir(t_pipex *p)
{
	int	i;
	int	error_flag;

	i = 0;
	error_flag = -1;
	if (!p)
		return (0);
	while (p)
	{
		i = 0;
		while (p->red_in && p->red_in[i])
		{
			if (!ft_strncmp(p->red_in[i], "STD:", 4) && error_flag == -1)
			{
				if (p->has_doc)
					close_fds(p->doc_pipe);
				p->has_doc = 0;
				if_close(p->in_fd);
				if (input_redir(p->red_in[i] + 4, p) < 0)
					error_flag = i;
			}
			else if (!ft_strncmp(p->red_in[i], "APP:", 4))
			{			
				if_close(p->in_fd);
				if (p->has_doc)
					close_fds(p->doc_pipe);
				p->has_doc = 1;
				if (do_here_doc(p->red_in[i] + 4, p) < 0)
					break ;
			} 
			i++;
		}
		p = p->next;
	}
	if (error_flag != -1)
		return (infile_error(p->red_in[error_flag]));
	return (1);
}
