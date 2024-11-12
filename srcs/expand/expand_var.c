#include "../minishel.h"

/*
loop to go through token list looking for places that need expansion
*/
void	expand_vars_loop(t_token *start)
{
	t_token	*step;

	step = start;
	while (step->next != NULL)
	{
		if (needs_expand(step))
			do_expand(step);
		else
			step = step->next;
	}
}

void	do_expand(t_token *t)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(t);
	var_value = get_var_value(mini_call()->env, var_name);
//	printf("var value is [%s]\n", var_value);
	expand_var(t, var_value);
	free(var_name);
	free(var_value);
}

/*
copys whatever comes before the var then adds the var_value and then whatever was after the var
*/
void	expand_var(t_token *t, char *var)
{
	char	*new;
	int		new_i;
	int		t_i;
	int		var_i;

	var_i = 0;
	new_i = 0;
	t_i = 0;
	new = safe_malloc(expanded_len(t, var));
	while (t->token[t_i] != '$')
		new[new_i++] = t->token[t_i++];
	while (var[var_i] != '\0')
		new[new_i++] = var[var_i++];
	t_i += var_name_len(t->token, t_i + 1) + 1;
	while (t->token[t_i] != '\0')
		new[new_i++] = t->token[t_i++];
	free(t->token);
	t->token = new;
}