#include "../minishell.h"


static bool	parse_pipe(t_token *t)//could already check for existence of words to left and right
{
	if (!t->previous)
		return (false);
	if (!t->next)
		return (false);
	if (t->next->token_type == PIPE)
		return (false);
	return (true);
}

static bool	parse_red(t_token *t)
{
	if (!t->next)
		return (false);
	if (t->next->token_type != WORD)
		return (false);
	return (true);
}

bool	first_parse(t_token *start)
{
	t_token	*step;

	step = start;
	while (step->next != NULL)
	{
		if (step->token_type == PIPE)
		{
			if(!parse_pipe(step))
				return (false);
		}
		else if (step->token_type == RED_APP || step->token_type == RED_IN ||
				step->token_type == RED_OUT || step->token_type == HERE_DOC)
		{
			if(!parse_red(step))
				return (false);
		}
		step = step->next;
	}
	return (true);
} 
