/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_out_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:04:42 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/17 21:53:59 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Prepares output redirection to append data to a file
*/
static int	app_redir_out(char *str, t_pipex *p)
{
	if (!str)
		return (0);
	if (!*str)
	{
		ft_put_str_fd("invalid outfile\n", 2);
		mini_call()->exit_status = 1;
		return (-1);
	}
	p->out_fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (p->out_fd == -1)
	{
		perror(str);
		mini_call()->exit_status = 1;
		return (-1);
	}
	return (1);
}

/*
Prepares output redirection overwrite a file
*/
static int	redir_out(char *str, t_pipex *p)
{
	if (!str)
		return (0);
	if (!*str)
	{
		ft_put_str_fd("invalid outfile\n", 2);
		mini_call()->exit_status = 1;
		return (-1);
	}
	p->out_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->out_fd == -1)
	{
		perror(str);
		mini_call()->exit_status = 1;
		return (-1);
	}
	return (1);
}

/*
Processes output redirections for all pipeline commands,
handling file creation, truncation, or append
*/
int	prep_output_redir(t_pipex *p)
{
	int	i;

	if (!p || !p->red_out)
		return (0);
	while (p)
	{
		i = -1;
		while (p->red_out && p->red_out[++i])
		{
			if (!ft_strncmp(p->red_out[i], "STD:", 4))
			{
				if_close(p->out_fd);
				if (redir_out(p->red_out[i] + 4, p) < 0)
				{
					p->bad_command = true;
					break ;
				}
			}
			else if (!ft_strncmp(p->red_out[i], "APP:", 4))
			{
				if_close(p->out_fd);
				if (app_redir_out(p->red_out[i] + 4, p) < 0)
				{
					p->bad_command = true;
					break ;
				}
			}
		}
		p = p->next;
	}
	return (1);
}
