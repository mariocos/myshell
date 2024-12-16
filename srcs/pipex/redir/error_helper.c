/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:47:44 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/14 18:47:37 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Handles and reports errors when creating a HEREDOC pipe
*/
int	here_pipe_error(void)
{
	perror("pipe");
	mini_call()->exit_status = 1;
	return (-1);
}

/*
Sets exit status to 1 and returns -1 for input file errors
*/
int	infile_error(void)
{
	mini_call()->exit_status = 1;
	return (-1);
}
