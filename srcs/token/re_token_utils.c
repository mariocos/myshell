/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:36:32 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/05 17:36:33 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
in case of operator preceding a word without a space
it will extract the operator from the word splitting the token into two
*/
t_token	*extract_operator(t_token *t)
{
	t_token	*new_t;
	t_token	*next_t;
	char	*help;

	help = ft_substr(t->token, 0, ft_isoperator(t->token, 0));
	new_t = init_token(help);
	free (help);
	help = ft_substr(t->token, ft_isoperator(t->token, 0), ft_strlen(t->token));
	next_t = init_token(help);
	free(help);
	new_t->next = next_t;
	next_t->previous = new_t;
	return (new_t);
}

/*
in case of word preceding a operator without a space
it will extract the word from the operator splitting the token into two
*/
t_token	*extract_word(t_token *token)
{
	t_token	*new_first;
	t_token	*new_second;
	char	*help;
	int		i;

	i = 0;
	while (ft_isoperator(token->token, i) == 0
		|| (ft_isoperator(token->token, i) > 0 && in_quote(token->token, i)))
		i++;
	help = ft_substr(token->token, 0, i);
	new_first = init_token(help);
	free(help);
	help = ft_substr(token->token, i, ft_strlen(token->token));
	new_second = init_token(help);
	free(help);
	new_first->next = new_second;
	new_first->next->previous = new_first;
	return (new_first);
}
