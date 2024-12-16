/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:01:53 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/16 12:51:43 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcat(char *dst, const char *src, char	*ret)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst && dst[i] != '\0')
	{
		ret[i] = dst[i];
		i++;
	}
	while (src && src[j] != '\0')
		ret[i++] = src[j++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*ret;

	s1_len = ft_strlen((const char *)s1);
	s2_len = ft_strlen((const char *)s2);
	ret = safe_malloc(s1_len + s2_len + 2);
	if (ret == NULL)
		return (NULL);
	ret[0] = '\0';
	ft_strcat((char *)s1, (char *)s2, ret);
	return (ret);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_put_str_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		write (fd, &str[i], 1);
		i++;
	}
}
