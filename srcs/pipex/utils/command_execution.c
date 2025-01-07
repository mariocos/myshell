/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:42:31 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/07 12:31:27 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Counts the number of variables in the environment linked list
*/
static int	count_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/*
Converts the environment linked list into a null-terminated array of strings
*/
char	**env_to_double_chr_ptr(t_env	*env)
{
	char	**env_chr_ptr;
	t_env	*tmp;
	int		i;
	int		j;

	tmp = env;
	i = count_env(env);
	env_chr_ptr = malloc(sizeof(char *) * (i + 1));
	if (!env_chr_ptr)
		return (NULL);
	tmp = env;
	j = 0;
	while (j < i)
	{
		env_chr_ptr[j] = ft_strdup(tmp->var);
		if (!env_chr_ptr[j++])
		{
			ft_free(env_chr_ptr);
			return (NULL);
		}
		tmp = tmp->next;
	}
	env_chr_ptr[j] = NULL;
	return (env_chr_ptr);
}

/*
Executes shell built-in commands like cd,
pwd, env, echo, unset, export, and exit
*/
void	exec_if_builtin(t_pipex *process)
{
	char	*cmd;

	cmd = process->cmd[0];
	if (!ft_strncmp(cmd, "cd", 2)
		&& ft_strlen(cmd) == 2 && process->pid != 0)
		cd(process->cmd, process->out_fd);
	else if (!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
		pwd(process->out_fd);
	else if (!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
		env(mini_call()->env, process->cmd, process->out_fd);
	else if (!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
		echo(process->cmd, process->out_fd);
	else if (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
		unset(process->cmd, mini_call()->env);
	else if (!ft_strncmp(cmd, "export\0", 7))
		export(process->cmd, process->out_fd);
	else if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
		exit_builtin(process->cmd);
	if (process->pid == 0)
		exit(mini_call()->exit_status);
}
