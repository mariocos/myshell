#include "../minishel.h"

int	ft_isspace(char c)
{
	if (c == 32 || (c <= 13 && c >= 9))
		return (1);
	return (0);
}

/*
returns 0 if not an operator and operator len if operator
*/
int	ft_isoperator(char *str, int i)//redo for clean
{
	if (str[i] == '<' && str[i + 1] == '<')
		return (2);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (2);
	else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (1);
	else
		return (0);
}