#include "../minishell.h"

int	count_pipes(t_token *t)
{
	int	pipe_amount;

	pipe_amount = 0;
	while (t)
	{
		if (t->token_type == PIPE)
			pipe_amount++;
		t = t->next;
	}
	return (pipe_amount);
}

t_pipex	*init_pipex(void)
{
	t_pipex	*ret;

	ret = (t_pipex *)safe_malloc(sizeof(t_pipex));
	ret->next = NULL;
	ret->previous = NULL;
	ret->red_in = NULL;
	ret->red_out = NULL;
	ret->cmd = NULL;
	return (ret);
}

void	pipex_add_back(t_pipex *start, t_pipex *add)
{
	t_pipex	*step;

	step = start;
	if (!start || !add)
		return ;
	while (step->next != NULL)
		step = step->next;
	step->next = add;
	add->previous = step;
}

t_pipex	*get_pipex_list(t_token	*t)
{
	int	pipe_amount;
	t_pipex	*start;
	t_pipex	*step;
	int	i;

	i = 0;
	pipe_amount = count_pipes(t);
	start = init_pipex();
	while (i < pipe_amount)
	{
		step = init_pipex();
		pipex_add_back(start, step);
		i++;
	}
	return (start);
}

void	tokens_to_pipex(t_token *t)
{
	t_pipex	*start;

	start = get_pipex_list(t);
	populate_pipex(t, start);
//	print_pipex_list(start);
	mini_call()->pipex_list = start;
}