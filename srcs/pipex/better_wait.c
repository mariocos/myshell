/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:19:19 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/12 18:31:53 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
