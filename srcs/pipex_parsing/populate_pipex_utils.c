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

char	**add_to_double_char_array(char **words, char *word)
{
	int	word_count;
	char	**ret;
	int	i;

	i = 0;
	if (!word)
		return (words);
	word_count = array_word_counter(words);
	if (!words)
	{
		ret = safe_malloc(sizeof(char **) * 2);
		ret[i] = word;
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
	i++;//added to see if it changes later change back to ret[++i]
	ret[i] = NULL;
	if (words)
		free_double_char_array(words);
	return (ret);
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