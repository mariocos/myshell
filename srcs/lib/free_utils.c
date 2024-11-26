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

void	free_pipex_list(t_pipex *p)
{
	while (p)
	{
		if (p->cmd)
			free_double_char_array(p->cmd);
		if (p->red_in)
			free_double_char_array(p->red_in);
		if (p->red_out)
			free_double_char_array(p->red_out);
		p = p->next;
	}
}


void	clean_all(void)
{
	t_mini	*m;

	m = mini_call();
	if (!m)
		return ;
	if (m->token)
		free_token_list(m->token);
	if (m->pipex_list)
		free_pipex_list(m->pipex_list);
}