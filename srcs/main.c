#include "minishell.h"

void	mini_loop(char **envp)
{
	mini_init(envp);
	while (1)
	{
		mini_call()->input = readline("mini>");
		if (!mini_call()->input)//chould change to if its equal to "exit"
			break ;
		input_handle();
		print_token_list(mini_call()->token);
		print_pipex_list(mini_call()->pipex_list);
	}
	clean_all();
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	
	if (argc == 1)
		mini_loop(envp);
	else
	{
		char *str = ft_strdup("\"$HOME\"");
		mini_init(envp);
		mini_call()->input = str;
		input_handle();
		print_token_list(mini_call()->token);
		print_pipex_list(mini_call()->pipex_list);
		clean_all();
	}
	return (0);
}
