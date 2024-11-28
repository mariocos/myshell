/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:42:31 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/11/28 14:29:54 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int count_env(t_env *env)
{
	int count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}


char **env_to_double_chr_ptr(t_env	*env)
{
	char 	**env_chr_ptr;
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

static bool	has_equal_sign(char *str)
{
	if (!str)
		return (false);
	while (*str)
		if (*str++ == '=')
			return (true);
	return (false);
}

void	exec_if_builtin(t_pipex *process)
{
	char *cmd;

	cmd = process->cmd[0];
	if (!ft_strncmp(cmd, "cd", 2) && ft_strlen(cmd) == 2)
		cd(process->cmd[1], mini_call()->env);
	else if (!ft_strncmp(cmd, "pwd", 3)	&& ft_strlen(cmd) == 3)
		pwd();
	else if (!ft_strncmp(cmd, "env", 3)	&& ft_strlen(cmd) == 3)
		env(mini_call()->env);
	else if (!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
		echo(process->cmd);
	else if (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
		unset(process->cmd[1], &(mini_call()->env));
	else if (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
		export(process->cmd[1], mini_call()->env, true);
	else if (has_equal_sign(cmd))
		export(process->cmd[0], mini_call()->env, false);
	else if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)	//Needs to be a builtin exit takes params
		exit(0);
}
