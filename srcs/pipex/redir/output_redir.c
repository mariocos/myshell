/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:43:18 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/11 12:01:18 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	do_out_redir(t_pipex *p)
{
	if (!p)
		return ;
	if (p->next != NULL)
	{
		dup2(p->pipe[1], STDOUT_FILENO);
		if_close(p->pipe[1]);
	}
	if (!p->red_out)
		return ;
	dup2(p->out_fd, STDOUT_FILENO);
}
