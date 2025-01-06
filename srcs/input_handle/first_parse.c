/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:13:55 by mariocos          #+#    #+#             */
/*   Updated: 2025/01/06 12:13:51 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	parse_pipe(t_token *t)
{
	if (t->previous == NULL)
		return (false);
	if (t->next == NULL)
		return (false);
	if (t->next->token_type == PIPE)
		return (false);
	return (true);
}

static bool	parse_red(t_token *t)
{
	if (!t->next)
		return (false);
	if (t->next->token_type != WORD)
		return (false);
	return (true);
}

bool	error_near_pipe(void)
{
	ft_put_str_fd("unexpected error near \"|\"\n", 2);
	return (false);
}

bool	err_near_redir(t_token *t)
{
	if (!t || !t->token || !*t->token)
	{
		ft_put_str_fd("error near redirections\n", 2);
		return (false);
	}
	if (!t->previous)
	{
		write (2, "error near newline\n", 19);
		return (false);
	}
	write(2, "error near \"", 12);
	write(2, &t->token[0], 1);
	write(2, "\"\n", 2);
	return (false);
}

bool	first_parse(t_token *start)
{
	t_token	*step;

	step = start;
	while (step)
	{
		if (step->token_type == PIPE)
		{
			if (!parse_pipe(step))
				return (error_near_pipe());
		}
		else if (step->token_type == RED_APP || step->token_type == RED_IN
			|| step->token_type == RED_OUT || step->token_type == HERE_DOC)
		{
			if (!parse_red(step))
				return (err_near_redir(step));
		}
		step = step->next;
	}
	return (true);
}
