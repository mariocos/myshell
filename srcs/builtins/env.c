/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 18:01:56 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/12/31 18:06:23 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	has_path_variable(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(env->var_name, "PATH", 5))
			return (true);
		env = env->next;
	}
	return (false);
}

static void	handle_invalid_arg(char **args, int fd)
{
	write(fd, "env: '", 6);
	write(fd, args[1], ft_strlen(args[1]));
	write(fd, "': No such file or directory\n", 29);
	mini_call()->exit_status = 127;
}

static void	print_env_variable(t_env *env, int fd)
{
	write(fd, env->var_name, ft_strlen(env->var_name));
	write(fd, "=", 1);
	write(fd, env->var_value, ft_strlen(env->var_value));
	write(fd, "\n", 1);
}

void	env(t_env *env, char **args, int fd)
{
	if (!env)
	{
		mini_call()->exit_status = 1;
		return ;
	}
	if (!has_path_variable(env))
	{
		write(2, "minishell: env: No such file or directory\n", 42);
		mini_call()->exit_status = 127;
		return ;
	}
	if (args[1])
	{
		handle_invalid_arg(args, fd);
		mini_call()->exit_status = 127;
		return ;
	}
	while (env != NULL)
	{
		if (env->exported)
			print_env_variable(env, fd);
		env = env->next;
	}
	mini_call()->exit_status = 0;
}
