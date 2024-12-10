/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:42:24 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/12/10 17:42:41 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_loop(char **envp)
{
	mini_init(envp);
	while (1)
	{
		mini_call()->input = readline("mini>");
		if (!mini_call()->input)
		{
			printf("exit\n");
			break ;
		}
		if (mini_call()->input && *mini_call()->input)
		{
			if (input_handle() == 1)
				process_handler(mini_call()->pipex_list);
		}
		clean_comand();
	}
	clean_all();
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	(void)argv;
	if (argc == 1)
	{
		setup_signal_handlers();
		mini_loop(envp);
	}
	else
	{
		str = ft_strdup("$$");
		mini_init(envp);
		mini_call()->input = str;
		input_handle();
		print_token_list(mini_call()->token);
		print_pipex_list(mini_call()->pipex_list);
		clean_all();
	}
	return (0);
}
