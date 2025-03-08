/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:41:18 by mariocos          #+#    #+#             */
/*   Updated: 2025/03/07 23:39:53 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	this function isnt in lib because its very specific
to the tokenization process, it splits a string by spaces
into a char**.
*/
int	count_words(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (!ft_isspace(s[i]) || (ft_isspace(s[i]) && in_quote(s, i)))
		{
			count++;
			while ((!ft_isspace(s[i]) || (ft_isspace(s[i])
						&& in_quote(s, i))) && s[i] != '\0')
				i++;
		}
		if (ft_isspace(s[i]) && !in_quote(s, i))
			i++;
	}
	return (count);
}

int	wordlen(char *s)
{
	int	i;

	i = 0;
	while ((!ft_isspace(s[i]) || (ft_isspace(s[i])
				&& in_quote(s, i))) && s[i] != '\0')
		i++;
	return (i);
}

char	**special_split(char const *s)
{
	char	**ret;
	int		wordcount;
	int		i;

	if (!s)
		return (NULL);
	wordcount = count_words(s);
	ret = safe_malloc(sizeof(char *) * (wordcount + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < wordcount)
	{
		while (ft_isspace(*s))
			s++;
		ret[i] = ft_substr((char *)s, 0, wordlen((char *)s));
		if (!ret[i])
			return (NULL);
		s += wordlen((char *)s);
	}
	ret[i] = NULL;
	return (ret);
}
