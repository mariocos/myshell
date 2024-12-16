/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:09:22 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/14 00:42:10 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Handles and reports errors when creating a pipe
*/
int	pipe_error(void)
{
	perror("pipe");
	mini_call()->exit_status = 1;
	return (-1);
}

/*
Handles and reports errors when creating a fork
*/
int	fork_error(void)
{
	perror("fork");
	mini_call()->exit_status = 1;
	return (-1);
}

/*
Closes both file descriptors in a given array, handling the first
*/
void	close_fds(int *fds)
{
	if_close(fds[0]);
	close(fds[1]);
}
