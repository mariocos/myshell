#include "../minishell.h"

void	populate_pipex(t_token *t_start, t_pipex *start)
{
	t_pipex	*step;
	t_token	*t;

	t = t_start;
	step = start;
	while (t)
	{
		if (t->token_type == HERE_DOC)
			step->red_in = add_handler(step->red_in, t->next->token, "APP:");
		else if (t->token_type == RED_IN)
			step->red_in = add_handler(step->red_in, t->next->token, "STD:");
		else if (t->token_type == RED_OUT)
			step->red_out = add_handler(step->red_out, t->next->token, "STD:");
		else if (t->token_type == RED_APP)
			step->red_out = add_handler(step->red_out, t->next->token, "APP:");
		else if (t->token_type == WORD)
			step->cmd = add_handler(step->cmd, t->token, NULL);
		else if (t->token_type == PIPE)
			step = step->next;
		if (t->token_type == WORD || t->token_type == PIPE)
			t = t->next;
		else
			t = t->next->next;
	}
}


/*
this function is dumb, i had to make it because functions can only have 25 lines max.
it creates a freeable string with the prefix appended to word, and adds it to the char**words 
using the add_to_double_char_array function
*/
char	**add_handler(char **words, char *word, char *prefix)
{
	char	*new_add;
	char	**ret;

	if (prefix)
		new_add = ft_strjoin(prefix, word);
	else
		new_add = ft_strdup(word);//im pretty sure this is correct now used to strdup prefix idkwhy
	ret = add_to_double_char_array(words, new_add);
	return (ret);
}

char	*ft_strcat(char *dst, const char *src, char	*ret)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] != '\0')
	{
		ret[i] = dst[i];
		i++;
	}
	while (src[j] != '\0')
		ret[i++] = src[j++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*ret;

	s1_len = ft_strlen((const char *)s1);
	s2_len = ft_strlen((const char *)s2);
	ret = safe_malloc(s1_len + s2_len + 2);//another magick number im not really sure why its needed but it makes the computer happy
	if (ret == NULL)
		return (NULL);
	ret[0] = '\0';
	ft_strcat((char *)s1, (char *)s2, ret);
	return (ret);
}
