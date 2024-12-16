/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:43:18 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/14 20:16:10 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Sets up stdout redirection to pipes or output files for the command
*/
void	do_out_redir(t_pipex *p)
{
	if (!p)
		return ;
	if (p->next != NULL)
	{
		dup2(p->pipe[1], STDOUT_FILENO);
		if_close(p->pipe[1]);
	}
	if (p->red_out == NULL)
		return ;
	dup2(p->out_fd, STDOUT_FILENO);
}
