/****************************************/
/*      (\__/)                          */
/*      (o^.^)                          */
/*     z(_(")_(")_                      */
/*                                      */
/*   Mariocos: minishell revamped       */
/****************************************/

#include "../../minishell.h"

/*
	this part is a bit complex so for info go to the readme
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

static char	*get_tilde_value(void)
{
	char *ret;

	ret = get_var_value(mini_call()->env, "HOME");
	if (ret == NULL)
	{
		ret = ft_strdup(mini_call()->home);
	}
	return (ret);
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
	expand = get_tilde_value();
	ret = safe_malloc(ft_strlen(expand) + ft_strlen(t->token) + 1);
	while (expand[exp_i] != '\0')
		ret[ret_i++] = expand[exp_i++];
	while (t->token[t_i] != '\0')
		ret[ret_i++] = t->token[t_i++];
	ret[ret_i] = '\0';
	free(expand);
	free(t->token);
	t->token = ret;
}
