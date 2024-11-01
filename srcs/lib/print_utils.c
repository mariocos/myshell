#include "../minishel.h"

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