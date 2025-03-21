/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hide_dolla.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:24:35 by mariocos          #+#    #+#             */
/*   Updated: 2025/03/21 12:10:35 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	Identifes cases where the Dollar sign is escaped by another character
and prevents it from being interpreted as an operator
*/
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

//undoes the previous funtion after expansions so we don get weird behaviours
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
