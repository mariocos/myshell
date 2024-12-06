#include "../minishell.h"

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
	while(str[i] != '=' && str[i])
		i++;
	new->var_name = ft_substr(str, 0, i);
	if (str[i] == '=')
	{
		new->var_value = ft_substr(str, i + 1, ft_strlen(str));
		new->exported = true;
	}
	else
	{
		new->var_value = ft_strdup("");
		new->exported = false;
	}
	new->next = NULL;
	new->previous = NULL;
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
	step->previous = step;
}

/*
initiates a minimal enviroment list for the "env -i ./minishell" situation
*/
t_env	*init_minimal_env(void)
{
	t_env	*start;
	char	cwd[4096];

	if(getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		exit(1);
	}
	start = init_var("PWD=");
	free(start->var_value);
	start->var_value = ft_strdup(cwd);
	var_add_back(start, init_var("LS_COLORS="));
	var_add_back(start, init_var("SHLVL=1"));
	var_add_back(start, init_var("PATH=/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin"));
	var_add_back(start, init_var("_=/usr/bin/env"));
	return (start);
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
		return(init_minimal_env());
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

/*
duplicates an enviroment list
*/
t_env	*env_dup(t_env *env)
{
	t_env	*new;
	t_env	*step;

	if (!env)
		return (NULL);
	new = init_var(env->var);
	step = env->next;
	while (step)
	{
		var_add_back(new, init_var(step->var));
		step = step->next;
	}
	return (new);
}