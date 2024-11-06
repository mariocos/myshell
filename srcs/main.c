#include "minishel.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char *str = ft_strdup("echo $HOME\"beans\"$HOME hello\">\"world >>test.txt| cat test.txt |cat ~");
	
	mini_init(envp);
	mini_call()->input = str;
	input_handle();
	print_token_list(mini_call()->token);
	return (0);
}