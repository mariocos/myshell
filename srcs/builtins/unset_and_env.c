/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_and_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:44:32 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/12/05 16:00:04 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(char *str, t_env **env)
{
	t_env	*tmp;
	t_env	*tmp_prev;

	if (!env || !*env || !str)
	{
		mini_call()->exit_status = 1;
		return ;
	}
	tmp = *env;
	if (!ft_strncmp(tmp->var_name, str, ft_strlen(str))
		&& ft_strlen(str) == ft_strlen(tmp->var_name))
	{
		*env = tmp->next;
		free_var(tmp);
		mini_call()->exit_status = 0;
		return ;
	}
	while (tmp != NULL)
	{
		tmp_prev = tmp;
		tmp = tmp->next;
		if (!ft_strncmp(tmp->var_name, str, ft_strlen(str))
			&& ft_strlen(str) == ft_strlen(tmp->var_name))
		{
			tmp_prev->next = tmp->next;
			free_var(tmp);
			mini_call()->exit_status = 0;
			return ;
		}
	}
	mini_call()->exit_status = 0;
}

void	env(t_env *env, int fd)
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
}
