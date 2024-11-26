#include "../minishell.h"
/*
special split works as normal split but ignores spaces in quotes
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
			while ((!ft_isspace(s[i]) || (ft_isspace(s[i]) && in_quote(s, i))) && s[i] != '\0')
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
	while (!ft_isspace(s[i]) || (ft_isspace(s[i]) && in_quote(s, i)))
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


/* int main() {
	char *str = "      echo hello|<<EOF \"beans   \" \"\"";
    char **words = ft_split(str);
	int	i = 0;


	while (words[i])
	{
		printf("[%s]\n",words[i]);
		i++;
	}
    return 0;
} */
