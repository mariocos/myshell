#include "../minishell.h"

/*
is special expand gets special expansions done

could use enum to mask the diferent types of special expansions to make code more readable
*/

int	is_special_expand(char *var_name)
{
	int var_len;

	var_len = ft_strlen(var_name);
	if (!ft_strncmp(var_name, "$", var_len))
		return (1);
	else if (!ft_strncmp(var_name, "?", var_len))
		return (1);
	else//add other special cases as i implement them
		return (0);
}

char	*get_special_var(char *var_name)//could be changed in order to just pass a enum mask
{
	int	var_len;

	var_len = ft_strlen(var_name);
	if (!ft_strncmp(var_name, "$", var_len))
		return (ft_itoa(getpid()));//gotta flesh this out
	else if (!ft_strncmp(var_name, "?", var_len))
	{
		return(ft_itoa(mini_call()->exit_status));
	}
	else
		return (ft_strdup(""));
}