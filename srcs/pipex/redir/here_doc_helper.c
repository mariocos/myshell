/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:16:09 by mario             #+#    #+#             */
/*   Updated: 2024/12/12 20:16:41 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*here_doc_expand(char *str)
{
	t_token	*t_help;
	char	*ret;

	if (!str || !*str)
		return (NULL);
	t_help = init_token(str);
	expand_vars_loop(t_help);
	ret = ft_strdup(t_help->token);
	free(str);
	free_token(t_help);
	return (ret);
}

void	help_free(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}
