/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hide_dolla.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:24:35 by mariocos          #+#    #+#             */
/*   Updated: 2025/03/07 23:39:43 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	hide_expand(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '$' && in_quote(str, i) && str[i + 1] == '\"')
			str[i] = OP_VAR;
		if (str[i] == '$' && in_squote(str, i))
			str[i] = OP_VAR;
		if (str[i] == '$' && str[i + 1] == '\'' && in_quote(str, i + 1))
			str[i] = OP_VAR;
		if (str[i] == '$' && str[i + 1] == '\0' && i != 0 && str[i - 1] != '$')
			str[i] = OP_VAR;
	}
}

void	unhide_expand(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == OP_VAR)
			str[i] = '$';
	}
}
