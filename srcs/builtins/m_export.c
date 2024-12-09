#include "../minishell.h"


/*
	called during init transforms env into export list.
*/


int ft_strcmp(const char* s1, const char* s2)//needs stress testing but should work
{
	if (!s1 || !s2)
	{
		printf("calling strcmp with NULL pointers\n");
		return (0);
	}
    while(*s1 && *s2 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

t_env	*get_head(t_env *e)
{
	while (e->previous != NULL)
		e = e->previous;
	return (e);
}

void	swap(t_env *e1, t_env *e2)
{
	e2->previous = e1->previous;
	if (e1->previous != NULL)
		e1->previous->next = e2;
	if (e2->next != NULL)
		e2->next->previous = e1;
	e1->next = e2->next;
	e2->next = e1;
	e1->previous = e2;
}

t_env	*sort_export_list(t_env *start)
{
	bool	go_back_flag;
	t_env	*step;

	go_back_flag = true;
	if (!start || !start->next)
		return (start);
	step = start;
	go_back_flag = false;
	while (step != NULL)
	{
		if (go_back_flag)//in case we repeat loop
			step = get_head(step);
		go_back_flag = false;
		if (step->next && strcmp(step->var_name, step->next->var_name) > 0)
		{
			go_back_flag = true;
			swap(step, step->next);
		}
		else if (step->next != NULL)
			step = step->next;
		if (step->next == NULL)
			break ;
	}
	return (get_head(step));
}

t_env	*get_export(t_env *env)
{
	t_env	*new;
	t_env	*start;
	t_env	*step;

	if (!env)//there should always be atleas minimal env
		return(NULL);
	step = env;
	start = init_var(step->var);
	step = step->next;
	while (step)
	{
		new = init_var(step->var);
		var_add_back(start, new);
		step = step->next;
	}
	start = sort_export_list(start);
	return (start);
}


void	ft_put_str_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] != '\0')
	{
		write (fd, &str[i], 1);
		i++;
	}
}

void	print_export(int fd)
{
	t_env	*step;

	step = mini_call()->export;
	while (step)
	{
		ft_put_str_fd("declare -x ", fd);
		ft_put_str_fd(step->var_name, fd);
		if (step->var_value && step->exported)
		{
			ft_put_str_fd("=\"", fd);
			ft_put_str_fd(step->var_value, fd);
			ft_put_str_fd("=\"", fd);
		}
		ft_put_str_fd("\n", fd);
		step = step->next;
	}
}

void	ft_init_export_list(void)
{
	t_env	*new_export;

	new_export = get_export(mini_call()->env);
	mini_call()->export = new_export;
//	print_export(1);
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

bool	has_equal(char *str)//by this point it should already be identified to be a valid export attempt
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
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

void	replace_var(t_env *start, t_env *new)
{
	t_env	*step;

	step = start;
	while (step)
	{
		if (!ft_strcmp(step->var_name, new->var_name))
			break ;
		step = step->next;
	}
	if (!step)
		printf("called replace var wrong, this var [%s] was not found", new->var_name);
	if (step->previous)
		step->previous->next = new;
	if (step->next)
		step->next->previous = new;
	new->next = step->next;
	new->previous = step->previous;
	free_var(step);
}

void	set_var(char *str)
{
	t_env	*new;

	new = init_var(str);
	if (var_exists(mini_call()->env, new))
		replace_var(mini_call()->env, new);
	else
		var_add_back(mini_call()->env, new);
	if (var_exists(mini_call()->export, new))
		replace_var(mini_call()->env, new);
	else
		smart_add(mini_call()->export, new);
}

void	smart_add(t_env *start, t_env *new)
{
	t_env	*step;

	step = start;//missing check if new should go on top of list
	while (step && strcmp(new->var_name, step->var_name) > 0)
		step = step->next;
	if (!step)
	{
		var_add_back(start, new);
		return ;
	}
	if (step->next)
		step->next->previous = new;
	new->next = step->next;
	step->next = new;
	new->previous = step;
}

void	prep_var(char *str)
{
	t_env	*new;

	new = init_var(str);
	if (!var_exists(mini_call()->export, new))
		smart_add(mini_call()->export, new);
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
		else if (has_equal(args[i]))
			set_var(args[i]);
		else
			prep_var(args[i]);
		i++;
	}
}
