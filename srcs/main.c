#include "minishell.h"
 
void	mini_loop(char **envp)
{
	mini_init(envp);
	while (1)
	{
		mini_call()->input = readline("mini>");
		if (!mini_call()->input)
		{
			printf("exit\n");
			break ;
		}
		if (mini_call()->input && !ft_strncmp(mini_call()->input, "exit\0", 5))//this is supposed to be a builtin:(
			break ;
		if (mini_call()->input && *mini_call()->input)
		{
			if (input_handle() == 1)
			{
//				print_token_list(mini_call()->token);
//				print_pipex_list(mini_call()->pipex_list);
				process_handler(mini_call()->pipex_list);
			}
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
	{
		setup_signal_handlers();
		mini_loop(envp);
	}
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
