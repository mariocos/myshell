/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:42:24 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/07 12:14:20 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
initializes minishell core struct (t_mini), continuously reads user input,
processes and executes commands, handles cleanup, and manages the shell's state
until the user exits
*/
void	mini_loop(char **envp)
{
	mini_init(envp);
	while (1)
	{
		mini_call()->input = readline("mini>");
		if (!mini_call()->input)
		{
			ft_put_str_fd("mexit\n", 2);
			break ;
		}
		if (mini_call()->input && *mini_call()->input)
		{
			mini_call()->line_nbr++;
			add_history(mini_call()->input);
			if (input_handle() == 1)
				process_handler(mini_call()->pipex_list);
			else
				mini_call()->exit_status = 2;
		}
		clean_comand();
	}
	clean_all();
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc == 1)
	{
		set_main_signals();
		mini_loop(envp);
	}
	return (0);
}
