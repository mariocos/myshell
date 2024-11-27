#include "../minishell.h"

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

int	ft_isalpha(char c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
		return (1);
	return (0);
}

int	ft_isdigit(char c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '"')
		return (1);
	else if (c == '\'')
		return (2);
	return (0);
}