/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:03:41 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/05 21:04:33 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtin(t_pipex *p)
{
	if (!p || !p->cmd)
		return (false);
	if (!ft_strncmp(p->cmd[0], "exit\0", 5))
		return (true);
	if (!ft_strncmp(p->cmd[0], "echo\0", 5))
		return (true);
	if (!ft_strncmp(p->cmd[0], "pwd\0", 4))
		return (true);
	if (!ft_strncmp(p->cmd[0], "cd\0", 3))
		return (true);
	if (!ft_strncmp(p->cmd[0], "export\0", 7))
		return (true);
	if (!ft_strncmp(p->cmd[0], "unset\0", 6))
		return (true);
	if (!ft_strncmp(p->cmd[0], "env\0", 4))
		return (true);
	return (false);
}
