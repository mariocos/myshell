/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:02:27 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/12/06 15:05:07 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	valid_var(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (false);
	while (var[i])
	{
		if (!ft_isalpha(var[i]) && !ft_isdigit(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static bool	update_var_values(t_env *tmp, char *str, int len)
{
	char	*new_var;
	char	*new_value;

	new_var = ft_strdup(str);
	new_value = ft_substr(str, len + 1, ft_strlen(str));
	if (!new_var || !new_value)
	{
		if (new_var)
			free(new_var);
		if (new_value)
			free(new_value);
		return (false);
	}
	free(tmp->var);
	free(tmp->var_value);
	tmp->var = new_var;
	tmp->var_value = new_value;
	return (true);
}

static bool	existing_var(t_env *tmp, char *var, char *str, int len)
{
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var_name, var, len) == 0
			&& ft_strlen(tmp->var_name) == ft_strlen(var))
		{
			if (str[len] == '=' && !update_var_values(tmp, str, len))
				return (true);
			tmp->exported = true;
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

static int	add_new_var(char *str, t_env *start, bool explicit_call)
{
	t_env	*new;

	new = init_var(str);
	if (!new)
	{
		mini_call()->exit_status = 1;
		return (1);
	}
	if (!explicit_call)
		new->exported = (false);
	var_add_back(start, new);
	mini_call()->exit_status = 0;
	return (0);
}

int	export(char *str, t_env *start, bool explicit_call)
{
	t_env	*tmp;
	char	*var;
	int		len;

	if (!str || !start)
	{
		mini_call()->exit_status = 1;
		return (1);
	}
	tmp = start;
	len = 0;
	while (str[len] != '=' && str[len])
		len++;
	var = ft_substr(str, 0, len);
	if (!valid_var(var))
	{
		free(var);
		mini_call()->exit_status = 1;
		return (1);
	}
	if (existing_var(tmp, var, str, len))
	{
		free(var);
		mini_call()->exit_status = 0;
		return (0);
	}
	free (var);
	return (add_new_var(str, start, explicit_call));
}

void	swap(t_env **stack)
{
	t_env	*first;
	t_env	*second;

	if (!stack || !*stack || !(*stack)->next)
		return ;

	first = *stack;
	second = first->next;

	if (first->previous)
		first->previous->next = second;

	first->next = second->next;
	second->next = first;

	second->previous = first->previous;
	first->previous = second;

	if (first->next)
		first->next->previous = first;
		
	*stack = second;
}

void	no_args_export(t_env *env, int fd)
{
	t_env *sorted_env;
	t_env *current;
	int		flag;

	if (!env)
		return ;
	sorted_env = env_dup(env);
	flag = 1;
	while (flag)
	{
		flag = 0;
		current = sorted_env;
		while (current->next)
		{
			if (ft_strncmp(current->var_name, current->next->var_name,
				ft_strlen(current->var_name)) > 0)
			{
				swap(&current);
				flag = 1;
			}
			else
				current = current->next;
		}
	}
	current = sorted_env;
	while (current)
	{
		write (fd, "declare -x ", 11);
		write (fd, current->var_name, ft_strlen(current->var_name));
		write (fd, "=\"", 2);
		write (fd, current->var_value, ft_strlen(current->var_value));
		write (fd, "\"\n", 2);
		current = current->next;
	}
	free_env_list(sorted_env);
	mini_call()->exit_status = 0;
}