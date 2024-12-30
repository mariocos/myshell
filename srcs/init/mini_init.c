/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:55:25 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/30 12:22:30 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Initializes the minishell global structure
*/
void	mini_init(char **env)
{
	t_mini	*mini;

	mini = mini_call();
	mini->token = NULL;
	mini->env = get_env(env);
	mini->input = NULL;
	mini->pwd = NULL;
	mini->pwd = getcwd(NULL, 0);
	mini->home = get_home();
	mini->exit_status = 0;
	mini->line_nbr = 0;
	mini->signaled = false;
}

/*
Implements a singleton, returning a pointer to the single, persistent instance
of the t_mini structure used to manage the minishell's global state
*/
t_mini	*mini_call(void)
{
	static t_mini	mini;

	return (&mini);
}

/*
retrieves the root user's home directory path
by truncating the current working directory
*/
char	*get_home(void)
{
	char	*wd;
	char	*ret;
	int		i;
	int		count_slash;

	i = 0;
	count_slash = 0;
	wd = NULL;
	wd = getcwd(NULL, 0);
	while (wd[i] != '\0')
	{
		if (wd[i] == '/')
			count_slash++;
		if (count_slash == 3)
			break ;
		i++;
	}
	ret = safe_malloc(i + 1);
	ret[i] = '\0';
	while (--i >= 0)
		ret[i] = wd[i];
	free(wd);
	return (ret);
}
