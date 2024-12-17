/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:47:59 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/17 20:10:33 by mariocos         ###   ########.fr       */
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

void	close_other_docs(t_pipex *p)
{
	t_pipex	*step;

	step = p->next;
	while (step != NULL)
	{
		if (step->has_doc)
			if_close(step->doc_pipe[0]);
		step = step->next;
	}
	step = step->previous;
	while (step != NULL)
	{
		if (step->has_doc)
			if_close(step->doc_pipe[0]);
		step = step->previous;
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

	if (!p || p->bad_command)
		exit (1);
	do_input_redir(p);
	do_out_redir(p);
//	close_other_docs(p);
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
		printf("going to exec cmd [%s]", p->cmd[0]);
		execve(path, p->cmd, envp);
		perror(p->cmd[0]);
	}
	exit(127);
}
