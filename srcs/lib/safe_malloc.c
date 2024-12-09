/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:59:05 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/05 20:59:41 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = s;
	while (i < n)
	{
		*ptr = c;
		i++;
		ptr++;
	}
	return (s);
}

/*
missing exit
*/
void	*safe_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
	{
		printf("\nA CRITICAL ERROR HAS OCCURRED\n\n");
		return (NULL);
	}
	ft_memset(ret, '\0', size);
	return (ret);
}
