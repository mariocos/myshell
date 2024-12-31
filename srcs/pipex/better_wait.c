/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:19:19 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/31 11:48:53 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Auxiliar function for ft_waitpid
*/
static void	handle_signaled(int status)
{
	if (WTERMSIG(status) == 2 && !mini_call()->signaled)
	{
		write(1, "\n", 1);
		mini_call()->signaled = true;
	}
	else if (WTERMSIG(status) == 3 && !mini_call()->signaled)
	{
		write(1, "Quit (no core dump)\n", 20);
		mini_call()->signaled = true;
	}
	mini_call()->exit_status = 128 + WTERMSIG(status);
}

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
		perror("waitpid");
		mini_call()->exit_status = 1;
		return ;
	}
	if (WIFEXITED(status))
		mini_call()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		handle_signaled(status);
	else
		mini_call()->exit_status = 1;
}
