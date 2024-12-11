/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twistft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:05:13 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/12/11 17:37:34 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjointwist(char *path, char *cmd)
{
	char	*jnt;
	size_t	i;
	size_t	j;

	if (!path || !cmd)
		return (NULL);
	i = 0;
	j = 0;
	jnt = (char *)malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(cmd) + 2));
	if (!jnt)
		return (NULL);
	while (path[i])
		jnt[j++] = path[i++];
	jnt[j++] = '/';
	i = 0;
	while (cmd[i])
		jnt[j++] = cmd[i++];
	jnt[j] = '\0';
	free(path);
	return (jnt);
}
