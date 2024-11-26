/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twistft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:05:13 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/11/25 17:26:30 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

/* 
static int	pre_len(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	test;

	i = 0;
	j = 0;
	test = 0;
	while (s1[i])
	{
		while (set[j])
		{
			if (s1[i] != set[j])
				test++;
			j++;
		}
		if (test == j)
			return (i);
		i++;
		j = 0;
		test = 0;
	}
	return (0);
}


static int	suf_len(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	test;

	i = ft_strlen(s1);
	j = 0;
	test = 0;
	while (i >= 0)
	{
		while (set[j])
		{
			if (s1[i - 1] != set[j])
				test++;
			j++;
		}
		if (test == j)
			return (ft_strlen(s1) - i);
		i--;
		j = 0;
		test = 0;
	}
	return (0);
}

char	*ft_strtrimtwist(char *s1, char const *set)
{
	char	*trimmed;
	size_t	i;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = ft_strlen(s1) - pre_len(s1, set) - suf_len(s1, set);
	trimmed = (char *) malloc (sizeof(char) * (len + 1));
	if (!trimmed)
		return (NULL);
	while (i < len)
	{
		trimmed[i] = s1[pre_len(s1, set) + i];
		i++;
	}
	trimmed[i] = '\0';
	free(s1);
	return (trimmed);
}
 */
