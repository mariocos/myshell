#include "minishel.h"

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// //	t_env	*env = get_env(envp);
// 	char str[100] = "echo $HOME hello\">\"world >>test.txt| cat test.txt";
// 	char **words = special_split(str);
	
// //	print_envp(env);
// 	print_double_array(words);
// 	t_token *tokens = input_split_to_token(words);
// 	print_token_list(tokens);
// 	printf("retokanizng\n");
// 	tokens = re_tokenize(tokens);
// 	print_token_list(tokens);
// 	if (first_parse(tokens) == true)
// 		printf("great\n");
// 	else
// 		printf("brerror\n");
// 	printf("finding vars\n");
// 	tokens = expand_vars(tokens);
// 	var_replace(tokens->next, "banana");
// 	return (0);
// }

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_env	*env = get_env(envp);
	
	print_envp(env);
	if (export("VAR=hello", env, true) == 1)
		printf("invalid var name: %s\n", "VAR=hello");
	if (export("VAR=hi", env, true) == 1)
		printf("invalid var name: %s\n", "VAR=hi");
	if (export("VAR1", env, true) == 1)
		printf("invalid var name: %s\n", "VAR1");
	if (export("1V", env, true) == 1)
		printf("invalid var name: %s\n", "1V");
	if (export("V@R", env, true) == 1)
		printf("invalid var name: %s\n", "V@R");
	if (export("V_R=man", env, true) == 1)
		printf("invalid var name: %s\n", "V_R=man");
	
	if (export("TEST=false", env, false) == 1)
		printf("invalid var name: %s\n", "V_R=man");

	// if (export("TEST=", env, true) == 1)
	// 	printf("invalid var name: %s\n", "V_R=man");


	print_envp(env);

	chk_not_exported(env);
	unset("V_R", &env);
	
	free_env_list(env);

	return (0);
}
