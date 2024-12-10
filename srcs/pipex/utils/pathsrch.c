/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathsrch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:12:30 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/12/10 16:55:22 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_env	*find_path_node(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var_name, "PATH", 4)
			&& ft_strlen(tmp->var_name) == 4)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	**get_paths(t_env *env)
{
	char	**paths;
	t_env	*path_node;

	path_node = find_path_node(env);
	if (!path_node || !path_node->var_value)
		return (NULL);
	paths = ft_split(path_node->var_value, ':');
	return (paths);
}

static char	*get_commandpath(char *command, char **paths)
{
	int		i;
	char	*commandpath;

	if (!command || !paths)
		return (NULL);
	i = 0;
	commandpath = NULL;
	while (paths[i])
	{
		paths[i] = ft_strjointwist(paths[i], command);
		if (access(paths[i], F_OK) != -1)
		{
			commandpath = ft_strdup(paths[i]);
			break ;
		}
		i++;
	}
	if (commandpath)
		return (commandpath);
	else
	{
		commandpath = ft_strdup(paths[0]);
		return (commandpath);
	}
}

char	*path_search(char *command, t_env *env)
{
	char	**paths;
	char	*path;

	if (!command || command[0] == '\0')
		return (NULL);
	paths = get_paths(env);
	path = get_commandpath(command, paths);
	if (paths)
		ft_free (paths);
	if (path)
		return (path);
	else
		return (NULL);
}
