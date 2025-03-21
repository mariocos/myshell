/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:25:00 by mariocos          #+#    #+#             */
/*   Updated: 2025/03/21 12:09:11 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	is special expand identifies special expansions
*/
int	is_special_expand(char *var_name)
{
	int	var_len;

	if (!*var_name)
		return (0);
	var_len = ft_strlen(var_name);
	if (!ft_strncmp(var_name, "$", var_len))
		return (1);
	if (!ft_strncmp(var_name, "?", var_len))
		return (1);
	else
		return (0);
}

/*
	get_special var returns the var value for
	the requested special expansion
*/
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
