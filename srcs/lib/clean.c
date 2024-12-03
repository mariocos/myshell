#include "../minishell.h"


void	clean_all(void)
{
	t_mini	*m;

	m = mini_call();
	if (!m)
		return ;
	if (m->input)
	{
		free (m->input);
		m->input = NULL;
	}
	if (m->token)
	{
		free_token_list(m->token);
		m->token = NULL;
	}
	if (m->pipex_list)
	{
		free_pipex_list(m->pipex_list);
		m->pipex_list = NULL;
	}
	if (m->env)
	{
		free_env_list(m->env);
		m->env = NULL;
	}
	clear_history();
    rl_clear_signals();
    rl_deprep_terminal(); 
}

void	clean_comand(void)//doesnt free mini_call()->input
{
	t_mini	*m;

	m = mini_call();
	if (!m)
		return ;
	if (m->token)
	{
		free_token_list(m->token);
		m->token = NULL;
	}
	if (m->pipex_list)
	{
		if (m->pipex_list->has_doc)
			close_fds(m->pipex_list->doc_pipe);
		free_pipex_list(m->pipex_list);
		m->pipex_list = NULL;
	}
	dup2(1,1);//just making sure no redirections from the previous command are still "open"
	dup2(0,0);
}