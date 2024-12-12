/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:20:47 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/12 13:21:42 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export_var(t_env *step, int fd)
{
	if (step != NULL)
	{
		ft_put_str_fd("declare -x ", fd);
		ft_put_str_fd(step->var_name, fd);
		if (step->var_value && step->exported)
		{
			ft_put_str_fd("=\"", fd);
			ft_put_str_fd(step->var_value, fd);
			ft_put_str_fd("\"", fd);
		}
		ft_put_str_fd("\n", fd);
	}
}

bool	is_next(t_env *step, int grade)
{
	t_env	*start;
	int		i;

	start = mini_call()->env;
	i = 0;
	while (start)
	{
		if (ft_strcmp(step->var_name, start->var_name) > 0)
			i++;
		start = start->next;
	}
	if (i == grade)
		return (true);
	return (false);
}

void	export_recursion(t_env *step, int fd)
{
	int	grade;

	grade = 0;
	while (step)
	{
		if (step && is_next(step, grade))
		{
			print_export_var(step, fd);
			grade++;
			step = mini_call()->env;
		}
		else
			step = step->next;
	}
}

void	print_export(int fd)
{
	t_env		*step;

	step = mini_call()->env;
	if (step)
		export_recursion(step, fd);
}
