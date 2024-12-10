/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_and_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:44:32 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/12/10 17:17:30 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_var(char *str)
{
	t_env	*step;

	if (!str || !mini_call()->env)
		return ;
	step = mini_call()->env;
	while (step)
	{
		if (!ft_strcmp(step->var_name, str))
		{
			if (step->previous)
				step->previous->next = step->next;
			if (step->next)
				step->next->previous = step->previous;
			free_var(step);
			break ;
		}
		step = step->next;
	}
}

void	unset(char **str, t_env *env)
{
	int	i;

	i = 1;
	if (!env || !env || !str)
	{
		mini_call()->exit_status = 1;
		return ;
	}
	if (str[i] == NULL)
		return ;
	while (str[i] != NULL)
	{
		remove_var(str[i]);
		i++;
	}
	mini_call()->exit_status = 0;
}

void	env(t_env *env, char **args, int fd)
{
	if (!env)
	{
		mini_call()->exit_status = 1;
		return ;
	}
	if (args[1])
	{
		write(fd, "env: '", 6);
		write(fd, args[1], ft_strlen(args[1]));
		write(fd, "': No such file or directory\n", 29);
		mini_call()->exit_status = 127;
		return ;
	}
	while (env != NULL)
	{
		if (env->exported)
		{
			write(fd, env->var_name, ft_strlen(env->var_name));
			write(fd, "=", 1);
			write(fd, env->var_value, ft_strlen(env->var_value));
			write(fd, "\n", 1);
		}
		env = env->next;
	}
	mini_call()->exit_status = 0;
}
/* void	env(t_env *env, int fd)
{
	if (!env)
	{
		mini_call()->exit_status = 1;
		return ;
	}
	while (env != NULL)
	{
		if (env->exported)
		{
			write(fd, env->var_name, ft_strlen(env->var_name));
			write(fd, "=", 1);
			write(fd, env->var_value, ft_strlen(env->var_value));
			write(fd, "\n", 1);
		}
		env = env->next;
	}
	mini_call()->exit_status = 0;
} */
