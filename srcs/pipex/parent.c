/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:36:15 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/10 20:09:21 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	spawn_child(t_pipex *p)
{
	if (!p)
		return (-1);
	if (pipe(p->pipe) < 0)
		return (pipe_error());
	p->pid = fork();
	if (p->pid < 0)
		return (fork_error());
	if (p->pid == 0)
		child_process_new(p);
	if (p->previous)
		close(p->previous->pipe[0]);
	close(p->pipe[1]);
	if (!p->next)
		close(p->pipe[0]);
	return (1);
}

int	prep_redir(t_pipex *p)
{
	if (prep_input_redir(mini_call()->pipex_list) < 0)
		return (-1);
	if (mini_call()->exit_status == 130 && p->has_doc)
		return (-1);
	if (mini_call()->exit_status == 144 && p->has_doc)
	{
		mini_call()->exit_status = 0;
		return (-1);
	}
	if (prep_output_redir(mini_call()->pipex_list) < 0)
		return (-1);
	return (1);
}

void	exec_single_comand(t_pipex *p)
{
	if (is_builtin(p))
	{
		exec_if_builtin(p);
	}
	else
	{
		p->pid = fork();
		if (p->pid == 0)
			child_process_new(p);
		ft_waitpid(p->pid);
	}
}

void	process_handler(t_pipex *p)
{
	if (prep_redir(p) < 0)
		return ;
	if (p->next == NULL)
		exec_single_comand(p);
	else
	{
		while (p != NULL)
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
}
