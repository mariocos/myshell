#include "../minishell.h"



void	hide_operators(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>')
			str[i] = OP_OUT;
		else if (str[i] == '<')
			str[i] = OP_IN;
		else if (str[i] == '|')
			str[i] == OP_PIPE;
		
	}
}



void	hide_operators_loop(t_token *t)
{
	t_token	*step;

	step = t;
	while(step)
	{
		if (step->token_type == WORD)
			hide_operators(step->token);
	}
}
