/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:16:22 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/10 21:00:46 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
detects a $[var_name] inside a token that isnt inside quotes
*/
bool	needs_expand(t_token *t)
{
	int	i;

	i = 0;
	if (!t || !t->token)
		return (false);
	if (ft_strlen(t->token) == 1 && t->token[0] == '$')
		return (false);
	while (t->token[i] != '\0')
	{
		if (t->token[i] == '$' && !in_squote(t->token, i))
			return (true);
		i++;
	}
	return (false);
}

/*
returns len of the var name ignoring the $
E.g. returns 4 for "$HOME"
*/
int	var_name_len(char *var_name, int i)
{
	int	len;

	len = 0;
	if (is_special_expand(var_name + i))
	{
		return (is_special_expand(var_name + i));
	}
	if (ft_isdigit(var_name[i]))
		return (1);
	if (!ft_isalpha(var_name[i]) && var_name[i] != '_')
		return (0);
	while (ft_isdigit(var_name[i + len])
		|| ft_isalpha(var_name[i + len]) || var_name[i + len] == '_')
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

	i = 0;
	while (t->token[i] != '$')
		i++;
	i++;
	if (t->token[i] == '$' || t->token[i] == '?')
	{
		return (ft_substr(t->token, i, 1));
	}
	else
		return (ft_substr(t->token, i, i + var_name_len(t->token, i)));
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
