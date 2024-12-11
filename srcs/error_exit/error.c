/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:27:38 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/11 16:50:53 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_perror(char *err_msg)
{
	int	i;

	i = 0;
	while (err_msg[i] != '\0')
	{
		write(1, &err_msg[i], 1);
	}
}

void	syntax_error(void)
{
	ft_put_str_fd("\na syntax error has ocurred :(\n\n", 2);
}
