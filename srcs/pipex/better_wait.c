/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:19:19 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/12 12:50:02 by mariocos         ###   ########.fr       */
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

/* void	ft_waitpid(int pid)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			mini_call()->exit_status = WIFEXITED(status);
		else if (WIFSIGNALED(status))
			mini_call()->exit_status = 128 + WTERMSIG(status);
	}
	if (mini_call()->exit_status == 130)
		write (2, "\n", 1);
	else if (mini_call()->exit_status == 131)
		ft_put_str_fd("core dumped\n", 2);
} */
