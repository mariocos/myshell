/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:16:09 by mario             #+#    #+#             */
/*   Updated: 2024/12/16 12:44:08 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Expands variables in a string for HEREDOC processing
*/
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

/*
Frees two strings if they are not NULL
*/
void	help_free(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

/*
Counts the number of digits in an integer
*/
int	ft_count_digits(int n)
{
	int		count;
	long	nbr;

	count = 0;
	nbr = n;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		nbr = -nbr;
	while (nbr)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

/*
Prints a warning for HEREDOC terminated by end-of-file (Ctrl+d)
*/
void	print_ctrl_d_msg(char *eof)
{
	char	*str;

	str = ft_itoa(mini_call()->line_nbr);
	write(2, "minishell: warning: here-document at line ", 42);
	write(2, str,
		ft_strlen(str));
	free(str);
	write(2, " delimited by end-of-file (wanted '", 35);
	write(2, eof, ft_strlen(eof));
	write(2, "')\n", 3);
}
