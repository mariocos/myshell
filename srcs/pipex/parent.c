/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:36:15 by mariocos          #+#    #+#             */
/*   Updated: 2025/01/03 12:16:09 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	set_parent_signals();
	p->pid = fork();
	if (!p->bad_command)
	{
		if (p->pid < 0)
			return (fork_error());
	}
	if (p->pid == 0)
	{
		set_signals_to_default();
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
Executes a single command without piping and waits for its completion
*/
void	exec_single_comand(t_pipex *p)
{
	if (p->bad_command)
	{
		printf("catching well\n");
		return ;
	}
	if (is_builtin(p))
	{
		exec_if_builtin(p);
	}
	else
	{
		set_signals_to_ignore();
		p->pid = fork();
		if (p->pid == -1)
		{
			perror("fork");
			mini_call()->exit_status = 1;
			return ;
		}
		if (p->pid == 0)
		{
			set_signals_to_default();
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
	if (rep_redir(p) < 0)
		return ;
	printf("[%d] made it here %d\n", p->in_fd, p->bad_command);
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
	set_main_signals();
}
