#include "../minishel.h"

/*
file that initializes the minishell struct
*/
void	mini_init(void)
{
	t_mini *mini;

	mini = mini_call();
	mini->token = NULL;
	mini->env = NULL;
	mini->export = NULL;
	mini->input = NULL;
	
}

t_mini	*mini_call(void)
{
	static t_mini	mini;

	return (&mini);
}