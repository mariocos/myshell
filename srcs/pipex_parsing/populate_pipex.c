/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:53:07 by mariocos          #+#    #+#             */
/*   Updated: 2025/01/03 14:11:56 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	populate_pipex(t_token *t_start, t_pipex *start)
{
	t_pipex	*step;
	t_token	*t;

	t = t_start;
	step = start;
	while (t != NULL)
	{
		if (t->token_type == HERE_DOC)
			step->red_in = add_handler(step->red_in, t->next->token, "APP:");
		else if (t->token_type == RED_IN)
			step->red_in = add_handler(step->red_in, t->next->token, "STD:");
		else if (t->token_type == RED_OUT)
			step->red_out = add_handler(step->red_out, t->next->token, "STD:");
		else if (t->token_type == RED_APP)
			step->red_out = add_handler(step->red_out, t->next->token, "APP:");
		else if (t->token_type == WORD)
			step->cmd = add_handler(step->cmd, t->token, NULL);
		else if (t->token_type == PIPE)
			step = step->next;
		if (t->token_type == WORD || t->token_type == PIPE)
			t = t->next;
		else
			t = t->next->next;
	}
}
