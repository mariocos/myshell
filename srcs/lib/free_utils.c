#include "../minishell.h"

void	free_token(t_token *t)
{
	if (t->token)
		free(t->token);
	free(t);
}

void	free_token_list(t_token *start)
{
	t_token	*step;
	t_token	*current;

	if (!start)
		return ;
	current = start;
	step = start;
	while (current->next != NULL)
	{
		step = current->next;
		free_token(current);
		current = step;
	}
}

void	free_var(t_env *var)
{
	if (!var)
		return ;
	free (var->var);
	free (var->var_name);
	free (var->var_value);
	free (var);
}

void	free_env_list(t_env *start)
{
	t_env	*step;

	if (!start)
		return ;
	while (start != NULL)
	{
		step = start->next;
		free_var(start);
		start = step;
	}
}

//Old version - last node remained intact and for that reason had a leak
/* void	free_env_list(t_env *start)
{
	t_env	*step;
	t_env	*current;

	if (!start)
		return ;
	step = start;
	current = start;
	while (current->next != NULL)
	{
		step = current->next;
		free_var(current);
		current = step;
	}
} */
