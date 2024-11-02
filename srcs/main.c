#include "minishel.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_env	*env = get_env(envp);
	char str[100] = "echo hello\">\"world >>test.txt| cat test.txt";
	char **words = special_split(str);
	
	print_envp(env);
	print_double_array(words);
	t_token *tokens = input_split_to_token(words);
	print_token_list(tokens);
	printf("retokanizng\n");
	tokens = re_tokenize(tokens);
	print_token_list(tokens);
	if (first_parse(tokens) == true)
		printf("great\n");
	else
		printf("brerror\n");
	return (0);
}