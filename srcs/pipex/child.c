/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:47:59 by mariocos          #+#    #+#             */
/*   Updated: 2025/01/03 13:25:44 by mariocos         ###   ########.fr       */
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

void	close_cmd_fds(t_pipex *p)
{
	if (!p)
		return ;
	if (p->has_doc)
		close(p->doc_pipe[0]);
	if (p->previous)
		close(p->previous->pipe[0]);
	if (p->next != NULL)
	{
		close(p->pipe[1]);
		close(p->pipe[0]);
	}
	exit(1);
}

static void	prt_execve_error_msg(char *command)
{
	t_env	*current;
	bool	has_path;

	has_path = false;
	current = mini_call()->env;
	while (current)
	{
		if (!ft_strncmp(current->var_name, "PATH", 5))
			has_path = true;
		current = current->next;
	}
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	if (!has_path)
		write(2, ": No such file or directory\n", 28);
	else
		write(2, ": command not found\n", 20);
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
		close_cmd_fds(p);
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
		execve(path, p->cmd, envp);
		prt_execve_error_msg(p->cmd[0]);
	}
	exit(127);
}
