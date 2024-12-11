/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:21:52 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/11 18:15:03 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
this file handles removing quotes from the pipex list things where it matters 
e.g.
[he""lo "heey" '"'] -> [helo heey "]
*/
int	remove_quote_len(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = -1;
	if (len == 0)
		return (0);
	while (str[++i] != '\0')
	{
		if (ft_isquote(str[i]) > 0)
		{
			len -= 2;
			i += advance_quotes(str, i) - 1;
		}
	}
	return (len);
}

int	advance_quotes(char *str, int i)
{
	int	len;

	len = i;
	if (str[len] == '"')
	{
		len++;
		while (str[len] != '"')
			len++;
		return (len + 1 - i);
	}
	else if (str[len] == '\'')
	{
		len++;
		while (str[len] != '\'')
			len++;
		return (len + 1 - i);
	}
	else
		return (-1);
}

void	remove_pipex_quotes(t_pipex *p)
{
	int	i;

	i = -1;
	while (p)
	{
		while (p->cmd && p->cmd[++i] != NULL)
			p->cmd[i] = rem_quote(p->cmd[i]);
		i = -1;
		while (p->red_in && p->red_in[++i])
			p->red_in[i] = rem_quote(p->red_in[i]);
		i = -1;
		while (p->red_out && p->red_out[++i])
			p->red_out[i] = rem_quote(p->red_out[i]);
		p = p->next;
	}
}
