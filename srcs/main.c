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
	char *str = ft_strdup("echo $HOME\"beans\"$HOME hello\">\"world >>test.txt| cat test.txt |cat");
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
	t_env	*ev = get_env(envp);
	
	print_envp(ev);
	if (export("VAR=hello", ev, true) == 1)
		printf("invalid var name: %s\n", "VAR=hello");
	if (export("VAR=yeah", ev, true) == 1)
		printf("invalid var name: %s\n", "VAR=yeah");
	if (export("VAR1=hi", ev, true) == 1)
		printf("invalid var name: %s\n", "VAR1=hi");
	if (export("1V", ev, true) == 1)
		printf("invalid var name: %s\n", "1V");
	if (export("AR1", ev, true) == 1)
		printf("invalid var name: %s\n", "AR1");
	// if (export("AR1=something", ev, false) == 1)
	// 	printf("invalid var name: %s\n", "AR1=something");
	if (export("V@R", ev, true) == 1)
		printf("invalid var name: %s\n", "V@R");
	if (export("V_R=man", ev, true) == 1)
		printf("invalid var name: %s\n", "V_R=man");
	
	if (export("TEST=false", ev, false) == 1)
		printf("invalid var name: %s\n", "TEST=false");

	//  if (export("TEST=", ev, true) == 1)
	// 	printf("invalid var name: %s\n", "TEST=");

	// unset("V_R", &ev);

	env(ev);

	pwd();
	cd("~/", ev);
	pwd();

	free_env_list(ev);

	char *args[] = {"-nnnnna", "THIS", "IS", "AN", "EXPERIENCE", NULL};

	echo(args);

	return (0);
}
