/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:42:33 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/11 12:16:36 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	do_input_redir(t_pipex *p)
{
	if (!p)
		return ;
	if (p->previous != NULL)
	{
		dup2(p->previous->pipe[0], STDIN_FILENO);
		if_close(p->previous->pipe[0]);
	}
	if (!p->red_in)
		return ;
	else
	{
		if (p->has_doc)
		{
			dup2(p->doc_pipe[0], STDIN_FILENO);
			if_close(p->doc_pipe[0]);
		}
		else
		{
			dup2(p->in_fd, STDIN_FILENO);
			if_close(p->in_fd);
		}
	}
}

void	prep_helper_file_opener(t_pipex *p, int *error_flag, int i)
{
	if (p->has_doc)
		close_fds(p->doc_pipe);
	p->has_doc = 0;
	if_close(p->in_fd);
	if (input_redir(p->red_in[i] + 4, p) < 0)
		*error_flag = i;
}

void	heredoc_helper(t_pipex *p)
{
	if_close(p->in_fd);
	if (p->has_doc)
		close_fds(p->doc_pipe);
	p->has_doc = 1;
}
