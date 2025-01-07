/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_prep2.0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:44:51 by mariocos          #+#    #+#             */
/*   Updated: 2025/01/07 14:44:54 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	app_outfile_opener(char *str, t_pipex *p)
{
	if (!str)
		return ;
	if (!*str)
	{
		ft_put_str_fd("invalid outfile\n", 2);
		mini_call()->exit_status = 1;
		p->bad_command = true;
		return ;
	}
	p->out_fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (p->out_fd == -1)
	{
		write (2, "minishell: ", 11);
		perror(str);
		mini_call()->exit_status = 1;
		p->bad_command = true;
		return ;
	}
}

static void	std_outfile_opener(char *str, t_pipex *p)
{
	if (!str)
		return ;
	if (!*str)
	{
		ft_put_str_fd("invalid outfile\n", 2);
		mini_call()->exit_status = 1;
		p->bad_command = true;
		return ;
	}
	p->out_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->out_fd == -1)
	{
		write (2, "minishell: ", 11);
		perror(str);
		mini_call()->exit_status = 1;
		p->bad_command = true;
		return ;
	}
}

void	open_outfiles_loop(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p->red_out)
		return ;
	while (p->red_out[i] != NULL)
	{
		if (!ft_strncmp(p->red_out[i], "STD:", 4))
			std_outfile_opener(p->red_out[i] + 4, p);
		else if (!ft_strncmp(p->red_out[i], "APP:", 4))
			app_outfile_opener(p->red_out[i] + 4, p);
		if (p->bad_command == true)
			break ;
		i++;
	}
}
