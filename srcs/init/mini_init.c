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
	mini->input = NULL;
	mini->home = get_home();
	mini->exit_status = 0;
	
}

t_mini	*mini_call(void)
{
	static t_mini	mini;

	return (&mini);
}

char	*get_home(void)
{
	char	*wd;
	char	*ret;
	int	i;
	int	count_slash;

	i = 0;
	count_slash = 0;
	wd = NULL;
	wd = getcwd(NULL, 0);
	while (wd[i] != '\0')
	{
		if (wd[i] == '/')
			count_slash++;
		if (count_slash == 3)
			break ;
		i++;
	}
	ret = safe_malloc(i + 1);//should already account for \0
	ret[i] = '\0';
	while (--i >= 0)
		ret[i] = wd[i];
	free(wd);
	return (ret);
}