/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_and_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:44:32 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/11/26 12:11:41 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(char *str, t_env **env)
{
	t_env	*tmp;
	t_env	*tmp_prev;

	if (!env || !*env || !str)
		return ;
	tmp = *env;
	if (!ft_strncmp(tmp->var_name, str, ft_strlen(str))
		&& ft_strlen(str) == ft_strlen(tmp->var_name))
	{
		*env = tmp->next;
		free_var(tmp);
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
			return ;
		}
	}
}

void	env(t_env *env)
{
	if (!env)
		return ;
	while (env != NULL)
	{
		if (env->exported)
			printf("%s=%s\n", env->var_name, env->var_value);
		env = env->next;
	}
}
