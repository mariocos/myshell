/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:19:19 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/10 17:32:38 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_waitpid(int pid)
{
	int	status;
	int	term_signal;

	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
			continue ;
		else
		{
			perror("waitpid");
			mini_call()->exit_status = 1;
			return ;
		}
	}
	if (WIFEXITED(status))
		mini_call()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		term_signal = WTERMSIG(status);
		mini_call()->exit_status = 128 + term_signal;
	}
	else
		mini_call()->exit_status = 1;
}
