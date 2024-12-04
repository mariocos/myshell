#include "../minishell.h"

void	hide_expand(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '$' && in_quote(str, i) && str[i + 1] == '\"')
		{
			printf("hiding va1r\n");
			str[i] = OP_VAR;
		}
		if (str[i] == '$' && in_squote(str, i))
		{
			printf("hide var2\n");
			str[i] = OP_VAR;
		}
	}
}

void	unhide_expand(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == OP_VAR)
			str[i] = '$';
	}
}