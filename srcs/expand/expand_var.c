/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:17:52 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/17 14:37:28 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
loop to go through token list looking
for places that need expansion and performing them
*/
void	expand_vars_loop(t_token *start)
{
	t_token	*step;

	step = start;
	while (step)
	{
		hide_expand(step->token);
		if (needs_expand(step))
			do_expand(step);
		else
		{
			unhide_expand(step->token);
			step = step->next;
		}
	}
}

void	do_expand(t_token *t)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(t);
	printf("var name is [%s]\n", var_name);
	if (is_special_expand(var_name))
		var_value = get_special_var(var_name);
	else
		var_value = get_var_value(mini_call()->env, var_name);
	printf("var value get is [%s]\n", var_value);
	expand_var(t, var_value);
	free(var_name);
	free(var_value);
}

static void	init_index(t_index *i)
{
	i->new_i = 0;
	i->t_i = 0;
	i->var_i = 0;
}

/*
i love ducks
*/
void	expand_var(t_token *t, char *var)
{
	char	*new;
	t_index	i;

	printf("var is [%s]\n", t->token);
	init_index(&i);
	new = safe_malloc(expanded_len(t, var) + 1);
	while (t->token[i.t_i] != '$')
		new[i.new_i++] = t->token[i.t_i++];
	while (var[i.var_i] != '\0')
		new[i.new_i++] = var[i.var_i++];
	if (t->token[i.t_i + 1] == '?' || t->token[i.t_i + 1] == '$')
		i.t_i += 2;
	else
		i.t_i += var_name_len(t->token, i.t_i + 1) + 1;
	while (t->token[i.t_i] != '\0')
		new[i.new_i++] = t->token[i.t_i++];
	new[i.new_i] = '\0';
	free(t->token);
	t->token = new;
}
