/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:02:39 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/05 21:02:40 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_len(int n)
{
	int	len;
	int	calc;

	len = 0;
	calc = n;
	if (n == 0)
		return (1);
	while (calc)
	{
		calc /= 10;
		len++;
	}
	if (n < 0)
		return (len + 1);
	else
		return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	short	len;
	long	nbr;
	short	i;

	i = 0;
	len = ft_len(n);
	str = (char *) safe_malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		nbr = -(long)n;
		i++;
	}
	else
		nbr = n;
	while (i < len)
	{
		str[(len--) - 1] = nbr % 10 + '0';
		nbr /= 10;
	}
	str[ft_len(n)] = '\0';
	return (str);
}
