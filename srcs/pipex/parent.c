/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:36:15 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/18 17:42:53 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Sets signal handling to its default state
*/
static void	set_sig_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/*
Spawns a child process for the given command,
setting up signals, pipes and executing it
*/
int	spawn_child(t_pipex *p)
{
	if (!p)
		return (-1);
	if (pipe(p->pipe) < 0)
		return (pipe_error());
	setup_signal_handlers_heredoc();
	p->pid = fork();
	if (!p->bad_command)
	{
		if (p->pid < 0)
			return (fork_error());
	}
	if (p->pid == 0)
	{
		set_sig_default();
		child_process_new(p);
	}
	if (p->previous)
		close(p->previous->pipe[0]);
	if (p->has_doc)
		close(p->doc_pipe[0]);
	if (p->next)
		close(p->pipe[1]);
	if (!p->next)
		close(p->pipe[0]);
	return (1);
}

/*
Prepares input and output redirections,
handling file openings and special cases before command execution
*/
int	prep_redir(t_pipex *p)
{
	if (prep_input_redir(mini_call()->pipex_list) < 0)
		return (-1);
	if (mini_call()->exit_status == 130 && p->has_doc)
		return (-1);
	if (mini_call()->exit_status == 144 && p->has_doc)
	{
		mini_call()->exit_status = 0;
		return (1);
	}
	if (prep_output_redir(mini_call()->pipex_list) < 0)
		return (-1);
	return (1);
}

/*
Executes a single command without piping and waits for its completion
*/
void	exec_single_comand(t_pipex *p)
{
	if (is_builtin(p))
	{
		exec_if_builtin(p);
	}
	else
	{
		setup_signal_handlers_spec();
		p->pid = fork();
		if (p->pid == -1)
		{
			perror("fork");
			mini_call()->exit_status = 1;
			return ;
		}
		if (p->pid == 0)
		{
			set_sig_default();
			child_process_new(p);
		}
		ft_waitpid(p->pid);
	}
}

/*
Coordinates command execution by setting up redirections,
running single or piped commands, and waiting for their completion
*/
void	process_handler(t_pipex *p)
{
	if (prep_redir(p) < 0)
		return ;
	if (!p->next)
		exec_single_comand(p);
	else
	{
		while (p)
		{
			if (spawn_child(p) < 0)
				return ;
			p = p->next;
		}
		p = mini_call()->pipex_list;
		while (p)
		{
			ft_waitpid(p->pid);
			p = p->next;
		}
	}
	setup_signal_handlers();
}
