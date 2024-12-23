/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:42:33 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/17 22:15:32 by mariocos         ###   ########.fr       */
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

/*
Manages input redirection by closing existing descriptors
and opening a specified file
*/
void	prep_helper_file_opener(t_pipex *p, int *error_flag, int i)
{
	if (p->has_doc)
		close_fds(p->doc_pipe);
	p->has_doc = 0;
	if_close(p->in_fd);
	if (input_redir(p->red_in[i] + 4, p) < 0)
	{
		p->bad_command = true;
		*error_flag = i;
	}
}

/*
Closes old input descriptors and marks the presence of a new HEREDOC
*/
void	heredoc_helper(t_pipex *p)
{
	if_close(p->in_fd);
	if (p->has_doc)
		close_fds(p->doc_pipe);
	p->has_doc = 1;
}
