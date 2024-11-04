#include "../minishel.h"

/*
this file handles the string utils needed to perform shell expansions
*/


/*
returns len of the var name 
E.g. returns 4 for "$HOME"
*/
int	advance_var(char *str, int i)//maybe change to receive only str and pass str + i when calling the function
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

bool	needs_expand(t_token *t)
{
	int	i;

	i = 0;
	if (!t || !t->token)
		return (false);
	while (t->token[i] != '\0')
	{
		if (t->token[i] == '$' && !in_quote(t->token, i))
			return (true);
		i++;
	}
	return (false);
}

/*
finds the var name of the first expansion in the token sent as parameter
*/
char	*get_var_name(t_token *t)
{
	int	i;
	int	name_len;
	char	*var_name;

	i = 0;
	name_len = 0;
	while (t->token[i] != '$' && t->token[i] != '\0')
		i++;
	if (t->token[i] != '$')
		return (NULL);
	name_len = advance_var(t->token, i);
	var_name = ft_substr(t->token, i, i + name_len);
	printf("%s\n", var_name);
	return (var_name);
}

/*
gonna be a similiar function to the 
*/
t_token	*expand_vars(t_token *start)
{
	t_token	*step;

	step = start;
	while (step->next != NULL)
	{
		print_token(step);
		if (needs_expand(step))
			
		step = step->next;
	}
	return (start);
}