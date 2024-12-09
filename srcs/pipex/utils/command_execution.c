/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:42:31 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/12/07 18:56:38 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

long	ft_atol(char *str)
{
	long	nbr;
	int		parity;

	nbr = 0;
	parity = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			parity++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	if (parity % 2 != 0)
		return (-nbr);
	return (nbr);
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
		export(process->cmd, process->out_fd, false);
	else if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
		exit_builtin(process->cmd[1]);
	if (process->pid == 0)
		exit(1);//just making sure we dont leave childs alive!
}
