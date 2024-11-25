#include "../minishell.h"

void	hide_expand(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '$' && in_squote(str, i))
			str[i] = OP_VAR;
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