/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:40:37 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/11/11 23:21:27 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

// Checks if a var is in the enviroment linked list
void	chk_env_var(char *str, t_env *start)
{
	t_env	*tmp;

	tmp = start;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var_name, str, ft_strlen(str)) == 0
			&& ft_strlen(str) == ft_strlen(tmp->var_name))
			printf("IT'S A MATCH: %s\n", tmp->var_name);
		tmp = tmp->next;
	}
}

// Checks if a var is not exported to the enviroment list
void	chk_not_exported(t_env *start)
{
	t_env	*tmp;

	tmp = start;
	while (tmp != NULL)
	{
		if (tmp->exported == false)
			printf("NOT EXPORTED: %s\n", tmp->var_name);
		tmp = tmp->next;
	}
}

// Different echo version
void	echo(char *str, bool n_flag)
{
	if (str && *str != '\0')
	{
		if (!n_flag)
			printf("%s\n", str);
		else
			printf("%s", str);
	}
	else if (!n_flag)
		printf("\n");
}
