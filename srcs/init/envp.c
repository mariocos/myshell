#include "../minishel.h"

/*
initializes a var node will be used for envp and export
*/
t_env	*init_var(char *str)
{
	t_env	*new;
	int	i;

	new = (t_env *)safe_malloc(sizeof(t_env));
	new->var = ft_strdup(str);
	i = 0;
	while(str[i] != '=')
		i++;
	new->var_name = ft_substr(str, 0, i);
	new->var_value = ft_substr(str, i, ft_strlen(str));
	new->next = NULL;
	return (new);
}

/*
simple list add back
*/
void	var_add_back(t_env *start, t_env *add)
{
	t_env	*step;

	step = start;
	while (step->next != NULL)
		step = step->next;
	step->next = add;
}

/*
populates list with envp
*/
t_env	*get_env(char **envp)
{
	t_env	*new;
	t_env	*start;
	int	i;

	if (count_strs(envp) == 0)
		return(NULL);
	start = init_var(envp[0]);
	i = 1;
	while (envp[i] != NULL)
	{
		new = init_var(envp[i]);
		var_add_back(start, new);
		i++;
	}
	return (start);
}