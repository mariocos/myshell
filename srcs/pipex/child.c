/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:47:59 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/11 12:24:08 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process_new(t_pipex	*p)
{
	char	**envp;
	char	*path;

	if (!p)
		return ;
	do_input_redir(p);
	do_out_redir(p);
	if (p->next != NULL || p->previous != NULL)
		close_fds(p->pipe);
	if (!p->cmd)
		exit(0);
	if (is_builtin(p))
		exec_if_builtin(p);
	else
	{
		printf("before exec %d\n", getpid());
		path = path_search(p->cmd[0], mini_call()->env);
		envp = env_to_double_chr_ptr(mini_call()->env);
		if (execve(path, p->cmd, envp) == -1)
			printf("EXECVE - NOTHING HAPPENED\n");
		perror("execve");
	}
	exit(127);
}
