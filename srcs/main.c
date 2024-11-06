#include "minishel.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char *str = ft_strdup("echo $HOME\"beans\"$HOME hello\">\"world >>test.txt| cat test.txt |cat ~");
	char **words = special_split(str);
	
	mini_init(envp);
	print_token_list(tokens);
	return (0);
}