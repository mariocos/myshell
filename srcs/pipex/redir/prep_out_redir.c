/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_out_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:04:42 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/12 20:26:19 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	app_redir_out(char *str, t_pipex *p)
{
	if (!str)
		return (0);
	if (!*str)
	{
		ft_put_str_fd("please use valide outfiles\n", 2);
		mini_call()->exit_status = 1;
		return (-1);
	}
	if (access(str, F_OK) != -1 && access(str, W_OK) == -1)
	{
		ft_put_str_fd("please use valid outfiles\n", 2);
		mini_call()->exit_status = 1;
		return (-1);
	}
	p->out_fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (1);
}

static int	redir_out(char *str, t_pipex *p)
{
	if (!str)
		return (0);
	if (!*str)
	{
		ft_put_str_fd("please use valide outfiles\n", 2);
		mini_call()->exit_status = 1;
		return (-1);
	}
	if (access(str, F_OK) != -1 && access(str, W_OK) == -1)
	{
		ft_put_str_fd("please use valid outfiles\n", 2);
		mini_call()->exit_status = 1;
		return (-1);
	}
	p->out_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (1);
}

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
					return (-1);
			}
			else if (!ft_strncmp(p->red_out[i], "APP:", 4))
			{
				if_close(p->in_fd);
				if (app_redir_out(p->red_out[i] + 4, p) < 0)
					return (-1);
			}
		}
		p = p->next;
	}
	return (1);
}
