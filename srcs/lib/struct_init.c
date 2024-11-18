#include "../minishell.h"

void	mini_init(void)
{
	mini_call()->token = NULL;
	mini_call()->input = NULL;
}

//allows to call reference to mini struct from anywhere
t_mini	*mini_call(void)
{
	static t_mini	mini;

	return (&mini);
}
