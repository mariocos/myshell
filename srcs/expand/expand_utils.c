#include "../minishel.h"

/*
detects a $[var_name] inside a token that isnt inside quotes
*/
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
returns len of the var name ignoring the $
E.g. returns 4 for "$HOME"
*/
int	var_name_len(char *str, int i)//maybe change a bit to return accounting for $
{
	int	len;

	len = 0;
	if (ft_isdigit(str[i]) || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (0);
	while (ft_isdigit(str[i + len]) || ft_isalpha(str[i + len]) || str[i + len] == '_')
		len++;
	return (len);
}

/*
calculates the len of the string after expansion
*/
int	expanded_len(t_token *t, char *var_value)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (t->token[i] != '$')
		i++;
	len += i;
	i += var_name_len(t->token, i);
	while (t->token[i] != '\0')
	{
		i++;
		len++;
	}
	return (len + ft_strlen(var_value));
}

/*
get_var_name and get_var_value always return a freeable str 
*/
char	*get_var_name(t_token *t)
{
	int	i;
	char *var_name;

	i = 0;
	while (t->token[i] != '$')
		i++;
	i++;
	var_name = ft_substr(t->token, i, i + var_name_len(t->token, i));
	return (var_name);
}

char	*get_var_value(t_env *env, char *var_name)
{
	if (!env || !var_name)
		return (NULL);
	while (env->next != NULL)
	{
		if (!ft_strncmp(var_name, env->var_name, ft_strlen(env->var_name)))
			return (ft_strdup(env->var_value));
		env = env->next;
	}
	return (ft_strdup(""));
}