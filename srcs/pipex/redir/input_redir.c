/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:42:33 by mariocos          #+#    #+#             */
/*   Updated: 2025/01/03 14:22:16 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Sets up stdin redirection from pipes, HEREDOC, or input files
for the current command
*/
void	do_input_redir(t_pipex *p)
{
	if (!p)
		return ;
	if (p->previous != NULL)
	{
		if (p->red_in == NULL)
			dup2(p->previous->pipe[0], STDIN_FILENO);
		close(p->previous->pipe[0]);
	}
	if (p->red_in != NULL)
	{
		if (p->has_doc == 1)
		{
			if (p->doc_pipe[0] != 0)
				dup2(p->doc_pipe[0], STDIN_FILENO);
			close(p->doc_pipe[0]);
		}
		else
		{
			if (p->in_fd != 0)
				dup2(p->in_fd, STDIN_FILENO);
			if_close(p->in_fd);
		}
	}
}
