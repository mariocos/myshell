#include "../minishel.h"

/*
this file handles the string utils needed to perform shell expansions
*/

int	advance_var(char *str, int i)
{
	int	len;

	len = 0;
	if (ft_isdigit(str[i]) || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (0);
	while (ft_isdigit(str[i + len]) || ft_isalpha(str[i + len]) || str[i + len] == '_')
		len++;
	return (len);
}

void	var_expand(char *dest, char *str, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '$')
	{
		dest[i] = str[i];
		i++;	
	}
	while (var[j] != '\0')
		dest[i++] = var[j++];
}


void	var_replace(t_token *t, char *var_value)
{
	int	len;
	int	i;
	char	*help;

	(void)help;
	i = 0;
	len = 0;
	while (t->token[i] != '\0')
	{
		if (t->token[i] == '$')
			i += advance_var(t->token, i);
		i++;
		len++;
	}
	help = safe_malloc(len + ft_strlen(var_value));//by here it should have the final len of the token even if theres two vars
	if (!help)
		return ;
	i = 0;
	var_expand(help, t->token, var_value);
	free (t->token);
	t->token = help;
	print_token(t);
}

