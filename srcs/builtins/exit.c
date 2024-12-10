/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:24:25 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/12/10 17:06:51 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long long	ft_atoll(const char *str)
{
	long long	nbr;
	int			parity;

	nbr = 0;
	parity = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			parity++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	if (parity % 2 != 0)
		return (-nbr);
	return (nbr);
}

static bool	is_numeric(const char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
		str++;
	if (!ft_isdigit(*str))
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

static bool	is_in_long_long_range(char *str)
{
	unsigned long long	threshold;
	unsigned long long	nbr;
	int					digit;

	threshold = (unsigned long long) LLONG_MAX;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			threshold++;
		str++;
	}
	nbr = 0;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (nbr > (threshold - digit) / 10)
			return (false);
		nbr = nbr * 10 + digit;
		str++;
	}
	return (true);
}

static int	calculate_exit_code(long long value)
{
	int	exit_code;

	exit_code = (unsigned long long)value % 256;
	return (exit_code);
}

void	exit_builtin(char **args)
{
	long long	value;
	int			exit_code;

	write(1, "exit\n", 5);
	if (!args[1])
		exit(EXIT_SUCCESS);
	if (!is_numeric(args[1]) || !is_in_long_long_range(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	value = ft_atoll(args[1]);
	exit_code = calculate_exit_code (value);
	exit(exit_code);
}
