/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_input_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:43:47 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/19 17:53:14 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Handles input redirection by validating and opening the specified file
*/
int	input_redir(char *str, t_pipex *p)
{
	p->in_fd = open(str, O_RDONLY);
	if (p->in_fd == -1)
	{
		write (2, "minishell: ", 11);
		perror(str);
		return (-1);
	}
	return (1);
}

/*
Closes file descriptor if it's greater than standard streams
*/
void	if_close(int fd)
{
	if (fd > 2)
		close (fd);
}

static int	handle_redirection_line(t_pipex *p, int i, int *error_flag)
{
	if (!ft_strncmp(p->red_in[i], "STD:", 4) && *error_flag == -1)
		prep_helper_file_opener(p, error_flag, i);
	else if (!ft_strncmp(p->red_in[i], "APP:", 4))
	{
		if (do_here_doc(p->red_in[i] + 4, p) < 0)
		{
			p->bad_command = true;
			return (-1);
		}
	}
	return (0);
}

/*
Processes input redirections and HEREDOC for all pipeline commands
*/
int	prep_input_redir(t_pipex *p)
{
	int	i;
	int	error_flag;

	error_flag = -1;
	if (!p)
		return (0);
	while (p)
	{
		i = -1;
		while (p->red_in && p->red_in[++i])
		{
			if (handle_redirection_line(p, i, &error_flag) < 0)
				break ;
		}
		p = p->next;
	}
	if (error_flag != -1)
		return (infile_error());
	return (1);
}
