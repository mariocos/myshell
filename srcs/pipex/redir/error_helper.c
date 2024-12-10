/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:47:44 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/10 15:52:06 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	here_pipe_error(void)
{
	ft_put_str_fd("crit error on pipe\n", 2);
	mini_call()->exit_status = 1;
	return (-1);
}

int	infile_error(void)
{
	ft_put_str_fd("bad input redirection file\n", 2);
	mini_call()->exit_status = 1;
	return (-1);
}

