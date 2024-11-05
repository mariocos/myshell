#include "minishel.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char str[100] = "echo $HOME\"beans\"$HOME hello\">\"world >>test.txt| cat test.txt";
	char **words = special_split(str);
	
	mini_init();
	mini_call()->env = get_env(envp);
//	print_envp(mini_call()->env);
//	print_double_array(words);
	t_token *tokens = input_split_to_token(words);
//	print_token_list(tokens);
//	printf("retokanizng\n");
	tokens = re_tokenize(tokens);
//	print_token_list(tokens);
	if (first_parse(tokens) == true)
		printf("great\n");
	else
		printf("brerror\n");
	printf("finding vars\n");
	expand_vars_loop(tokens);
	printf("wey\n");
	print_token_list(tokens);
	return (0);
}