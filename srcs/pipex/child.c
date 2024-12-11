/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:47:59 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/11 15:11:43 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	char	hold;

	hold = c;
	while (*s)
	{
		if (*s == hold)
			return ((char *)s);
		s++;
	}
	if (hold == '\0')
		return ((char *)s);
	return (0);
}

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
		if (!ft_strchr(p->cmd[0], '/'))
			path = path_search(p->cmd[0], mini_call()->env);
		else
			path = p->cmd[0];
		envp = env_to_double_chr_ptr(mini_call()->env);
		if (execve(path, p->cmd, envp) == -1)
			printf("EXECVE - NOTHING HAPPENED\n");
		perror("execve");
	}
	exit(127);
}
