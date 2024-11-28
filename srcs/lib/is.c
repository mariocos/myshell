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

bool	is_builtin(t_pipex *p)
{
	if (!p || !p->cmd)
		return (false);
	if (!ft_strncmp(p->cmd[0], "exit\0", 5))
		return (true);
	if (!ft_strncmp(p->cmd[0], "echo\0", 5))
		return (true);
	if (!ft_strncmp(p->cmd[0], "pwd\0", 4))
		return (true);
	if (!ft_strncmp(p->cmd[0], "cd\0", 3))
		return (true);
	if (!ft_strncmp(p->cmd[0], "export\0", 7))
		return (true);
	if (!ft_strncmp(p->cmd[0], "unset\0", 6))
		return (true);
	if (!ft_strncmp(p->cmd[0], "env\0", 4))
		return (true);
	return (false);	
}