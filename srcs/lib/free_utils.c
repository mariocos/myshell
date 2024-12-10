/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:04:49 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/10 19:37:14 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_token *t)
{
	if (!t)
		return ;
	free(t->token);
	free(t);
}

void	free_token_list(t_token *start)
{
	t_token	*step;
	t_token	*current;

	if (!start)
		return ;
	current = start;
	step = start;
	while (current)
	{
		step = current->next;
		free_token(current);
		current = step;
	}
}

void	free_var(t_env *var)
{
	if (!var)
		return ;
	if (var->var != NULL)
		free (var->var);
	if (var->var_name != NULL)
		free (var->var_name);
	if (var->var_value != NULL)
		free (var->var_value);
	free (var);
}

void	free_env_list(t_env *start)
{
	t_env	*step;

	if (!start)
		return ;
	while (start)
	{
		step = start->next;
		free_var(start);
		start = step;
	}
}

void	free_pipex_list(t_pipex *p)
{
	t_pipex	*help;

	while (p)
	{
		help = p->next;
		//close_fds(p->pipe);
		if (p->cmd)
			free_double_char_array(p->cmd);
		if (p->red_in)
			free_double_char_array(p->red_in);
		if (p->red_out)
			free_double_char_array(p->red_out);
		free(p);
		p = help;
	}
}
