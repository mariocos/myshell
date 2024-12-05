/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:20:49 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/05 18:21:43 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	parse_quotes(const char *input)
{
	int		i;
	bool	in_quote;
	bool	in_squote;

	i = 0;
	in_quote = false;
	in_squote = false;
	while (input[i] != '\0')
	{
		if (input[i] == '\"' && !in_squote)
			in_quote = !in_quote;
		else if (input[i] == '\'' && !in_quote)
			in_squote = !in_squote;
		i++;
	}
	if (!in_quote && !in_squote)
		return (true);
	return (false);
}

bool	in_quote(const char *input, int index)
{
	int		i;
	bool	q_flag;
	bool	s_flag;

	i = 0;
	q_flag = false;
	s_flag = false;
	while (i < index && input[i] != '\0')
	{
		if (input[i] == '\"' && !s_flag)
			q_flag = !q_flag;
		else if (input[i] == '\'' && !q_flag)
			s_flag = !s_flag;
		i++;
	}
	if (!q_flag && !s_flag)
		return (false);
	return (true);
}

bool	in_squote(const char *input, int index)
{
	int		i;
	bool	q_flag;
	bool	s_flag;

	i = 0;
	q_flag = false;
	s_flag = false;
	while (i < index && input[i] != '\0')
	{
		if (input[i] == '\"' && !s_flag)
			q_flag = !q_flag;
		else if (input[i] == '\'' && !q_flag)
			s_flag = !s_flag;
		i++;
	}
	if (!q_flag && !s_flag)
		return (false);
	if (!q_flag && s_flag)
		return (true);
	return (false);
}
