#include "minishell.h"

void	mini_loop(char **envp)
{
	mini_init(envp);
	while (1)
	{
		mini_call()->input = readline("mini>");
		if (!mini_call()->input)
			break ;
		input_handle();
//		clean_all();
		print_token_list(mini_call()->token);
	}
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
		char *str = ft_strdup("echo $$ <<in $ \"$\"HOME beans $HOME hello\">\"world >>test.txt| cat test.txt |cat ~");
		mini_init(envp);
		mini_call()->input = str;
		input_handle();
		print_token_list(mini_call()->token);
		clean_all();
	}
	return (0);
}
