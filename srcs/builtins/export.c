#include "../minishel.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < (n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// Returns 0 in case of success and 1 in case of failure, call option true for an explicit call
int	export(char *str, t_env *start, bool call)
{
	t_env	*tmp;
	t_env	*new;
	char	*var;
	int		i;

	tmp = start;
	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	var = ft_substr(str, 0, i);
	i = 0;
	while (var[i])
	{
		if (!ft_isalpha(var[0]) || (!ft_isalpha(var[i]) && !ft_isdigit(var[i]) && var[i] != '_'))
			return (1);
		i++;
	}
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var_name, var, i) == 0)			//Caso var exista
		{
			if (str[i] == '=') 					//Situação 'export VAR='
			{
				free(tmp->var);
				free(tmp->var_value);
				tmp->var = ft_strdup(str);
				tmp->var_value = ft_substr(str, i + 1, ft_strlen(str));
			}
			tmp->exported = true;
			free(var);
			return (0);
		}
		tmp = tmp->next;
	}
	free (var);
	new = init_var(str);				//Caso var não exista
	if (!call)
		new->exported = false;
	var_add_back(start, new);
	return (0);
}

void	chk_not_exported(t_env *start)
{
	t_env	*tmp;

	tmp = start;
	while (tmp != NULL)
	{
		if (tmp->exported == false)
			printf("NOT EXPORTED: %s\n", tmp->var_name);
		tmp = tmp->next;
	}
}


// ➜  myshell git:(hugo) ✗ unset VAR=      
// unset: VAR=: invalid parameter name
// ➜  myshell git:(hugo) ✗ echo $?
// 1

void unset(char *str, t_env **env)
{
	t_env	*tmp;
	t_env	*tmp_prev;

	if (!env || !*env)
		return ;

	tmp = *env;
	if (!ft_strncmp(tmp->var_name, str, ft_strlen(str)) && ft_strlen(str) == ft_strlen(tmp->var_name))
	{
		*env = tmp->next;
		free_var(env);
		return ;
	}
	while (tmp != NULL)
	{
		tmp_prev = tmp;
		tmp = tmp->next;
		if (!ft_strncmp(tmp->var_name, str, ft_strlen(str)) && ft_strlen(str) == ft_strlen(tmp->var_name))
		{
			tmp_prev->next = tmp->next;
			free_var(tmp);
			return ;
		}
	}
}

/* void	chk_export_var(char *str, t_env *start)
{
	(void)str;
	t_env	*tmp;
	char	*var;

	tmp = start;
	var = str;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var, var, (int)ft_strlen(var)) == 0 && ft_strlen(var) == ft_strlen(tmp->var_name))			//Caso var exista
			printf("IT'S A MATCH: %s\n", tmp->var_name);
		tmp = tmp->next;
	}
} */	
