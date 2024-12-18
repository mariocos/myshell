/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 23:10:51 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/12/18 23:16:26 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Handles HEREDOC input, expands variables, writes to a pipe,
and exits on completion
*/
static void	process_input_and_write(char *help, int doc_pipe_fd)
{
	char	*str;

	if (*help)
		str = here_doc_expand(help);
	else
		str = help;
	help = ft_strjoin(str, "\n");
	write(doc_pipe_fd, help, ft_strlen(help));
	help_free(help, str);
}

void	read_into_pipe(char *eof, t_pipex *p)
{
	char	*help;

	if_close(p->doc_pipe[0]);
	while (1)
	{
		help = readline("> ");
		if (help == NULL)
		{
			close(p->doc_pipe[1]);
			print_ctrl_d_msg(eof);
			free(help);
			exit(144);
		}
		if (!ft_strcmp(help, eof))
		{
			free(help);
			break ;
		}
		process_input_and_write(help, p->doc_pipe[1]);
	}
	close(p->doc_pipe[1]);
	exit(0);
}

static void	wait_and_restore_signal_handlers(int pid, t_pipex *p)
{
	setup_signal_handlers_heredoc();
	if_close(p->doc_pipe[1]);
	ft_waitpid(pid);
	setup_signal_handlers();
}

/*
Handles HEREDOC by creating pipes, managing child process input, and
synchronizing with the parent with signal and error handling
*/
int	do_here_doc(char *str, t_pipex *p)
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
	wait_and_restore_signal_handlers(pid, p);
	if (p->has_doc && mini_call()->exit_status != 0)
		return (-1);
	return (1);
}
