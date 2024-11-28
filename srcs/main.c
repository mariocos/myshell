#include "minishell.h"
 
void	mini_loop(char **envp)
{
	mini_init(envp);
	while (1)
	{
		mini_call()->input = readline("mini>");
		if (!ft_strncmp(mini_call()->input, "exit\0", 5))//chould change to if its equal to "exit"
			break ;
		if (mini_call()->input && *mini_call()->input)
		{
			input_handle();
			print_token_list(mini_call()->token);
			print_pipex_list(mini_call()->pipex_list);
		}
		clean_comand();
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
		char *str = ft_strdup("$$");
		mini_init(envp);
		mini_call()->input = str;
		input_handle();
		print_token_list(mini_call()->token);
		print_pipex_list(mini_call()->pipex_list);
		clean_all();
	}
	return (0);
}


/* valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all  
 --suppressions=".valgrind.supp" ./minishell*/