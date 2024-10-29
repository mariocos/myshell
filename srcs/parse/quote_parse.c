#include "../minishel.h"

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
			in_quote = !in_quote;//this reverses the bool
		else if (input[i] == '\'' && !in_quote)
			in_squote = !in_squote;
		i++;
	}
	if (!in_quote && !in_squote)
		return (true);
//	syntax_error("please close your quotes");// mi but should update status to know to clean and print error
	return (false);
}
//returns false if not in quote and true if in quote

bool	in_quote(const char *input, int index)
{
	int	i;
	bool	q_flag;
	bool	s_flag;

	i = 0;
	q_flag = false;
	s_flag = false;
	while (i < index)
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


/* char	*input_to_token(char *input)
{
	char	**words;

	if (!input || !parse_quotes(input))
		return (NULL);
	words = ft_special_split(input);
} */
