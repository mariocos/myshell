/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_double_char_array.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:40:57 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/10 15:29:11 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**helper(int i, char *word)
{
	char	**ret;

	ret = safe_malloc(sizeof(char *) * 3);
	ret[i] = word;
	return (ret);
}

char	**add_to_double_char_array(char **words, char *word)
{
	int		word_count;
	char	**ret;
	int		i;

	i = 0;
	if (!word)
		return (words);
	word_count = array_word_counter(words);
	if (!words)
	{
		printf("going to create char**\n");
		ret = helper(i, word);
	}
	else
	{
		ret = safe_malloc(sizeof(char *) * (word_count + 2));
		while (i < word_count)
		{
			ret[i] = ft_strdup(words[i]);
			i++;
		}
		ret[i] = word;
	}
	i++;
	ret[i] = NULL;
	if (words)
		free_double_char_array(words);
	return (ret);
}
