#include "../minishell.h"

void	print_double_array(char **words)
{
	int	i;

	i = -1;
	if (!words)
	{
		printf("char ** missing\n");
		return ;
	}
	while (words[++i] != NULL)
	{
		printf("ind %d [%s]\n", i,  words[i]);
	}
}

void	print_token_list(t_token *start)
{
	if (!start)
	{
		printf("token pointer missing\n");
		return ;
	}
	while (start->next != NULL)
	{
		if (!start->token)
			printf("token content is missing\n");
		else
			printf("token content is [%s] and token type %d\n", start->token, start->token_type);
		start = start->next;
	}
	printf("token content is [%s] and token type %d\n", start->token, start->token_type);
}

void	print_token(t_token *token)
{
	if (!token)
	{
		printf("missing token\n");
		return ;
	}
	printf("token content is [%s]\n", token->token);
}

void	print_envp(t_env *env)
{
	if (!env)
		return ;
	while (env != NULL)
	{
//		printf("\npointer to var %p previos %p next %p\n", env, env->previous, env->next);
		printf("var [%s], var name[%s], var value [%s]\n",env->var, env->var_name, env->var_value);
		env = env->next;
	}
}

void	print_pipex_list(t_pipex *start)
{
	if (!start)
	{
		printf("naughty naughty calling print pipex with bad pointer\n");
		return ;
	}
	int	i = 0;
	printf("gonna print pipex list\n");
	while (start)
	{
		printf("ind is %d\n", i);
		printf("\nprinting input redirections\n");
		print_double_array(start->red_in);
		printf("\nprinting output redirections\n");
		print_double_array(start->red_out);
		printf("\nprinting comands\n");
		print_double_array(start->cmd);
		printf("\nprinting path\n");
		start = start->next;
		i++;
	}
}
