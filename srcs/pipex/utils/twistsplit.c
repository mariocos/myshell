/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twistsplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:07:52 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/12/03 14:22:30 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
		i++;
	while (i > 0)
		free(argv[--i]);
	free(argv);
}

static size_t	ft_cntstr(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	*ft_slice(char const *s, char c, size_t *x)
{
	char	*slice;
	size_t	start;
	size_t	len;
	size_t	i;

	while (s[*x] && s[*x] == c)
		(*x)++;
	start = *x;
	len = 0;
	while (s[*x + len] != c && s[*x + len])
		len++;
	slice = (char *)malloc(len + 1);
	if (!slice)
		return (NULL);
	i = 0;
	while (i < len)
	{
		slice[i] = s[start + i];
		i++;
	}
	slice[len] = '\0';
	*x += len;
	return (slice);
}

char	**ft_split(char const *s, char c)
{
	char	**slices;
	size_t	count;
	size_t	y;
	size_t	x;

	if (!s)
		return (NULL);
	count = ft_cntstr(s, c);
	slices = (char **)malloc(sizeof(char *) * (count + 1));
	if (!slices)
		return (NULL);
	y = 0;
	x = 0;
	while (y < count)
	{
		slices[y] = ft_slice(s, c, &x);
		if (!slices[y])
		{
			ft_free(slices);
			return (NULL);
		}
		y++;
	}
	slices[y] = (NULL);
	return (slices);
}
