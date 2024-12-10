/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:05:23 by mariocos          #+#    #+#             */
/*   Updated: 2024/12/10 20:48:52 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_all(void)
{
	t_mini	*m;

	m = mini_call();
	if (!m)
		return ;
	if (m->home)
		free(m->home);
	if (m->input)
		free (m->input);
	if (m->token)
		free_token_list(m->token);
	if (m->pipex_list)
		free_pipex_list(m->pipex_list);
	if (m->env)
		free_env_list(m->env);
	clear_history();
	rl_clear_signals();
	rl_deprep_terminal();
}

void	clean_comand(void)
{
	t_mini	*m;

	m = mini_call();
	if (!m)
		return ;
	if (m->input)
		free(m->input);
	if (m->token)
	{
		free_token_list(m->token);
		m->token = NULL;
	}
	if (m->pipex_list)
	{
		if (m->pipex_list->has_doc == 1)
			close_fds(m->pipex_list->doc_pipe);
		if_close(m->pipex_list->in_fd);
		if_close(m->pipex_list->out_fd);
		free_pipex_list(m->pipex_list);
		m->pipex_list = NULL;
	}
}
