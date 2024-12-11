/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:09:22 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/11 18:14:21 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_error(void)
{
	ft_put_str_fd("critical error creating a pipe\n", 2);
	mini_call()->exit_status = 1;
	return (-1);
}

int	fork_error(void)
{
	ft_put_str_fd("a critical error has occured trying to fork\n", 2);
	mini_call()->exit_status = 1;
	return (-1);
}

void	close_fds(int *fds)
{
	if_close(fds[0]);
	close(fds[1]);
}
