/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:24:09 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/11 18:14:53 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	copy_quote(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (src[i] == '\'')
	{
		i++;
		while (src[i] != '\'')
			dest[j++] = src[i++];
	}
	else if (src[i] == '\"')
	{
		i++;
		while (src[i] != '\"')
			dest[j++] = src[i++];
	}
}

static void	rem_quote_helper(int i, int ret_i, char *str, char *ret)
{
	while (str[++i] != '\0')
	{
		if (ft_isquote(str[i]) > 0)
		{
			copy_quote(ret + ret_i, str + i);
			ret_i += advance_quotes(str, i) - 2;
			i += advance_quotes(str, i) - 1;
		}
		else
			ret[ret_i++] = str[i];
	}
	ret[ret_i] = '\0';
}

char	*rem_quote(char *str)
{
	char	*ret;
	int		i;
	int		ret_i;

	i = -1;
	ret_i = 0;
	if ((int)ft_strlen(str) == remove_quote_len(str))
		return (str);
	ret = safe_malloc(remove_quote_len(str) + 1);
	if (remove_quote_len(str) == 0)
		ret[0] = '\0';
	else
		rem_quote_helper(i, ret_i, str, ret);
	free(str);
	return (ret);
}
