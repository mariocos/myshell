/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_input_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:43:47 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/17 22:14:56 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Handles HEREDOC input, expands variables, writes to a pipe,
and exits on completion
*/
void	read_into_pipe(char *eof, t_pipex *p)
{
	char	*str;
	char	*help;

	if_close(p->doc_pipe[0]);
	while (1)
	{
		help = readline("> ");
		if (help == NULL)
		{
			close(p->doc_pipe[1]);
			print_ctrl_d_msg(eof);
			free (help);
			exit (144);
		}
		if (!ft_strcmp(help, eof))
		{
			free(help);
			break ;
		}
		if (*help)
			str = here_doc_expand(help);
		else
			str = help;
		help = ft_strjoin(str, "\n");
		write(p->doc_pipe[1], help, ft_strlen(help));
		help_free(help, str);
	}
	close(p->doc_pipe[1]);
	exit(0);
}

/*
Handles HEREDOC by creating pipes, managing child process input, and
synchronizing with the parent with signal and error handling
*/
static int	do_here_doc(char *str, t_pipex *p)
{
	int	pid;

	if (p->has_doc == 1)
		close(p->doc_pipe[0]);
	p->has_doc = 1;
	if (pipe(p->doc_pipe) < 0)
		return (here_pipe_error());
	pid = fork();
	if (pid < 0)
	{
		close_fds(p->doc_pipe);
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		setup_child_process_signal_handlers();
		read_into_pipe(str, p);
	}
	setup_signal_handlers_heredoc();
	if_close(p->doc_pipe[1]);
	ft_waitpid(pid);
	setup_signal_handlers();
	if (p->has_doc && mini_call()->exit_status != 0)
		return (-1);
	return (1);
}

/*
Handles input redirection by validating and opening the specified file
*/
int	input_redir(char *str, t_pipex *p)
{
	p->in_fd = open(str, O_RDONLY);
	if (p->in_fd == -1)
	{
		perror(str);
		return (-1);
	}
	return (1);
}

/*
Closes file descriptor if it's greater than standard streams
*/
void	if_close(int fd)
{
	if (fd > 2)
		close (fd);
}

/*
Processes input redirections and HEREDOC for all pipeline commands
*/
int	prep_input_redir(t_pipex *p)
{
	int	i;
	int	error_flag;

	error_flag = -1;
	if (!p)
		return (0);
	while (p)
	{
		i = -1;
		while (p->red_in && p->red_in[++i])
		{
			if (!ft_strncmp(p->red_in[i], "STD:", 4) && error_flag == -1)
				prep_helper_file_opener(p, &error_flag, i);
			else if (!ft_strncmp(p->red_in[i], "APP:", 4))
			{
				if (do_here_doc(p->red_in[i] + 4, p) < 0)
				{
					p->bad_command = true;
					break ;
				}
			}
		}
		p = p->next;
	}
	if (error_flag != -1)
		return (infile_error());
	return (1);
}
