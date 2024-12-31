/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:44:32 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/12/31 18:04:19 by hugo-mar         ###   ########.fr       */
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
