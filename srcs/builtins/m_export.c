#include "../minishell.h"


/*
	called during init transforms env into export list.
*/


int ft_strcmp(const char *s1, const char *s2)//needs stress testing but should work
{
	if (s1 == NULL || s2 == NULL)
	{
		printf("calling strcmp with NULL pointers\n");
		return (0);
	}
    while(*s1 && *s2 && (*s1 == *s2))
    {
		if (!*s1 || !*s2)
			break ;
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}


void	ft_put_str_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		write (fd, &str[i], 1);
		i++;
	}
}

void	print_export(int fd)
{
	t_env	*step;

	step = mini_call()->env;
	while (step != NULL)
	{
		ft_put_str_fd("declare -x ", fd);
		ft_put_str_fd(step->var_name, fd);
		if (step->var_value && step->exported)
		{
			ft_put_str_fd("=\"", fd);
			ft_put_str_fd(step->var_value, fd);
			ft_put_str_fd("\"", fd);
		}
		ft_put_str_fd("\n", fd);
		step = step->next;
	}
}

bool	invalid_export(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
		i++;
	if (str[i] != '\0' || str[i] != '=')//after this its the var_value that can be whatever
		return (false);
	return (true);
}

bool	var_exists(t_env *start, t_env *new)
{
	t_env	*step;

	step = start;
	while (step)
	{
		if (!ft_strcmp(step->var_name, new->var_name))
			return (true);
		step = step->next;
	}
	return (false);
}


void	export(char **args, int fd)
{
	printf("heloo from export\n");
	int	i;

	i = 1;
	mini_call()->exit_status = 0;
	if (args[1] == NULL)
	{
		print_export(fd);
		return ;
	}
	while (args[i] != NULL)
	{
		if (invalid_export(args[i]))//done but needs testing
			mini_call()->exit_status = 1;
		else
			var_add_back(mini_call()->env, init_var(args[i]));
		i++;
	}
}


/* int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char **help = ft_split("a b c d e f g", ' ');

	mini_call()->env = get_env(help);
	mini_call()->export = get_export(mini_call()->env);
	print_envp(mini_call()->export);
	set_var(ft_strdup("a=1"));
	print_export(1);
} */