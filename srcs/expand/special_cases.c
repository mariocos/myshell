/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:25:00 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/17 14:40:49 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
is special expand gets special expansions done
could use enum to mask the diferent types of
special expansions to make code more readable
*/

int	is_special_expand(char *var_name)
{
	int	var_len;

	if (!*var_name)
		return (0);
	var_len = ft_strlen(var_name);
	if (!ft_strncmp(var_name, "$", var_len))
		return (1);
	else if (!ft_strncmp(var_name, "?", var_len))
		return (1);
	else
		return (0);
}

char	*get_special_var(char *var_name)
{
	int	var_len;

	var_len = ft_strlen(var_name);
	if (!ft_strncmp(var_name, "$", var_len))
		return (ft_itoa(getpid()));
	else if (!ft_strncmp(var_name, "?", var_len))
	{
		return (ft_itoa(mini_call()->exit_status));
	}
	else
		return (ft_strdup(""));
}
