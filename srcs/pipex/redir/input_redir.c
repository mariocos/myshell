/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:42:33 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/10 14:43:01 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	do_input_redir(t_pipex *p)
{
	if (!p)
		return ;
	if (p->previous)
	{
		dup2(p->previous->pipe[0], STDIN_FILENO);
		close(p->previous->pipe[0]);
	}
	if (!p->red_in)
		return ;
	else
	{
		if (p->has_doc)
		{
			dup2(p->doc_pipe[0], STDIN_FILENO);
			close(p->doc_pipe[0]);
		}
		else
		{
			dup2(p->in_fd, STDIN_FILENO);
			close(p->in_fd);
		}
	}
}
