#include "../minishel.h"


/*
called when a token has a token followed by another
*/
t_token	*extract_operator(t_token *t)
{
	t_token	*new_t;
	t_token	*next_t;
	char	*help;

	help = ft_substr(t->token, 0, ft_isoperator(t->token, 0));
	new_t = init_token(help);
	free (help);
	help = ft_substr(t->token, ft_isoperator(t->token, 0), ft_strlen(t->token));
	next_t = init_token(help);
	free(help);
	new_t->next = next_t;
	next_t->previous = new_t;
	return (new_t);
}


t_token	*extract_word(t_token *token)
{
	t_token	*new_first;
	t_token	*new_second;
	char	*help;
	int	i;

	i = 0;
	while (ft_isoperator(token->token, i) == 0
		|| (ft_isoperator(token->token, i) > 0 && in_quote(token->token, i)))
		i++;
	help = ft_substr(token->token, 0, i);
	new_first = init_token(help);
	free(help);
	help = ft_substr(token->token, i, ft_strlen(token->token));
	new_second = init_token(help);
	free(help);
	new_first->next = new_second;
	new_first->next->previous = new_first;
	return (new_first);
}