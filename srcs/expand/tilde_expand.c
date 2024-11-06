#include "../minishel.h"

/*
expands tilde to $HOME
due to the necessites of tilde expansion (read README)
since i split the tokens by spaces the only time theres gonna be a valid tilde to expand
is if its at the begining of the token
*/
void	tilde_loop(t_token *t)
{
	while (t->next != NULL || t->token[0] == '~')
	{
		if (t->token[0] == '~')
			expand_tilde(t);
		else
			t = t->next;
	}
}

void	expand_tilde(t_token *t)
{
	char	*expand;
	char	*ret;
	int		ret_i;
	int		t_i;
	int		exp_i;

	ret_i = 0;
	t_i = 1;
	exp_i = 0;
	expand = get_var_value(mini_call()->env, "HOME");
	ret = safe_malloc(ft_strlen(expand) + ft_strlen(t->token));
	while (expand[exp_i] != '\0')
		ret[ret_i++] = expand[exp_i++];
	while (t->token[t_i] != '\0')
		ret[ret_i++] = t->token[t_i++];
	ret[++ret_i] = '\0';
	free(t->token);
	t->token = ret;
}