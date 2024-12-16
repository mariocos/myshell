/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:47:59 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/16 22:22:17 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Finds the first occurrence of a character in a string,
returning its pointer or NULL if not found
*/
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

static void	close_docs(void)
{
	t_pipex	*p;

	p = mini_call()->pipex_list;
	while (p)
	{
		if (p->has_doc)
			if_close(p->doc_pipe[0]);
		p = p->next;
	}
}
/*
Manages redirections, executes builtins, or
runs external commands in a child process
*/
void	child_process_new(t_pipex	*p)
{
	char	**envp;
	char	*path;

	if (!p)
		return ;
	do_input_redir(p);
	do_out_redir(p);
	close_docs();
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
		execve(path, p->cmd, envp);
		perror(p->cmd[0]);
	}
	exit(127);
}
