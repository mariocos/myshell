/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:19:19 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/14 19:55:08 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Waits for a child process, handles signals, and updates the global exit status
*/
void	ft_waitpid(int pid)
{
	int	status;

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
		if (status == 2)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == 3)
			write(1, "SEGFAULT CORE DUMPED(you asked for this)\n", 41);
		mini_call()->exit_status = 128 + WTERMSIG(status);
	}
	else
		mini_call()->exit_status = 1;
}
