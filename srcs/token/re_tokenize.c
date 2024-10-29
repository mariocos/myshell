#include "../minishel.h"

/*
tokens have already been created and separated by spaces, now the operators need to be separated
*/
t_token	*re_tokenize(t_token *start)
{
	t_token	*step;

	step = start;
 	while (step->next != NULL)
	{
		if (needs_retoken(step->token))
		{
			step = token_reasign(step);
		}
		else
			step = step->next;
	}
	while (step->previous != NULL)
	{
		step = step->previous;
	}
	return (step);
}

/*
receives a str and checks the existence of a valid operator, meaning its not in quotes and is part
of the operators in the subject.
*/
bool	needs_retoken(char *str)
{
	int	i;
	bool	has_op;
	bool	has_words;

	i = 0;
	has_op = false;
	has_words = false;
	while (str[i] != '\0')
	{
		if (ft_isoperator(str, i) && !in_quote(str, i))
			has_op = true;
		else
			has_words = true;
		i++;
	}
	if (has_op && has_words)
		return (true);
	return (false);
}

bool	ft_isoperator(char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '<')
		return (true);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (true);
	else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (true);
	else
		return (false);
}

t_token	*token_separate(t_token *token)//revisit in order to make it less than 25 lines
{
	t_token	*new_first;
	t_token	*new_second;
	char	*help;
	int	i;

	i = 0;
	if (ft_isoperator(token->token, 0))
	{
		while (ft_isoperator(token->token, i))
			i++;
		help = ft_substr(token->token, 0, i);
		new_first = init_token(help);
		free(help);
		help = ft_substr(token->token, i, ft_strlen(token->token));
		new_second = init_token(help);
		free(help);
		new_first->next = new_second;
		new_first->next->previous = new_first;
	}
	else
	{
		while (!ft_isoperator(token->token, i))
			i++;
		help = ft_substr(token->token, 0, i);
		new_first = init_token(help);
		free(help);
		help = ft_substr(token->token, i, ft_strlen(token->token));
		new_second = init_token(help);
		free(help);
		new_first->next = new_second;
		new_first->next->previous = new_first;
	}
	return (new_first);
}

t_token	*token_reasign(t_token *t)
{
	t_token	*new;
//	t_token	*help;

	new = token_separate(t);
	if (t->next != NULL)
	{
		new->next->next = t->next;
	}
	if (t->previous != NULL)
	{
		t->previous->next = new;
		new->previous = t->previous;
	}
	free_token(t);
	return (new);
}
