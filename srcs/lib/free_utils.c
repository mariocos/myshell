#include "../minishel.h"

void	free_token(t_token *t)
{
	if (t->token)
		free(t->token);
	free(t);
}