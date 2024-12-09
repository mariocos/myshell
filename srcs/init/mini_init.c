#include "../minishell.h"

/*
file that initializes the minishell struct
*/
void	mini_init(char **env)
{
	t_mini *mini;

	mini = mini_call();
	mini->token = NULL;
	mini->env = get_env(env);
	mini->export = NULL;
	ft_init_export_list();
	mini->input = NULL;
	mini->exit_status = 0;
	
}

t_mini	*mini_call(void)
{
	static t_mini	mini;

	return (&mini);
}
