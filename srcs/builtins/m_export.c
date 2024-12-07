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
	{
		printf("get_head\n");
		e = e->previous;
	}
	return (e);
}

void	swap(t_env *e1, t_env *e2)
{
	printf("\nin swap\n");
	printf("swaping %s and %s\n", e1->var, e2->var);
	if (e1->previous)
	{
		e1->previous->next = e2;
		e2->previous = e1->previous;
	}
	if (!e1->previous)
		e2->previous = NULL;
	if (e2->next)
	{
		e2->next->previous = e1;
		e1->next = e2->next;
	}
	if (!e2->next)
		e1->next = NULL;
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
		printf("hey1\n");
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
	print_envp(start);
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

void	ft_init_export_list(void)
{
	t_env	*new_export;

	new_export = get_export(mini_call()->env);
	mini_call()->export = new_export;
	print_envp(new_export);
}
