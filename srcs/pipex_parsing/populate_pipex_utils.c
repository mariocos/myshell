/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_pipex_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:53:23 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/05 19:53:54 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	array_word_counter(char	**words)
{
	int	i;

	i = 0;
	if (!words)
		return (0);
	while (words[i] != NULL)
		i++;
	return (i);
}

void	free_double_char_array(char **words)
{
	int	i;

	i = 0;
	if (!words)
		return ;
	while (words[i] != NULL)
	{
		if (words[i])
			free(words[i]);
		i++;
	}
	free(words);
}

/*
Add handler adds prefix to beggining of string before adding it to the char **words.
*/
char	**add_handler(char **words, char *word, char *prefix)
{
	char	*new_add;
	char	**ret;

	if (prefix)
		new_add = ft_strjoin(prefix, word);
	else
		new_add = ft_strdup(word);
	ret = add_to_double_char_array(words, new_add);
	return (ret);
}