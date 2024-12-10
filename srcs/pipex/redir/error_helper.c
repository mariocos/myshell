/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:47:44 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/10 14:50:30 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	here_pipe_error(void)
{
	ft_put_str_fd("crit error on pipe\n", 2);
	return (-1);
}

int	infile_error(char *error_msg)
{
	printf("bad infile %s\n", error_msg);
	return (-1);
}

