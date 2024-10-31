#include "../minishel.h"

/*
file that initializes the minishell struct
*/
void	mini_init(void)
{
	mini_call()->
}

t_mini	*mini_call(void)
{
	static t_mini	mini;

	return (&mini);
}