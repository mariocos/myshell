#include "../../../minishell.h"

int	check_if_doc_final(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p->red_in)
		return (0);
	while (p->red_in[i] != NULL)
	{
		if (!ft_strncmp(p->red_in[i], "APP:", 4))
			p->has_doc = 1;
		else
			p->has_doc = 0;
		i++;
	}
	return (1);
}

int	rep_input_redir(t_pipex *start)
{
	t_pipex *p;

	p = start;
	while (p)
	{
		check_if_doc_final(p);
		if (do_docs_loop(p) < 0)
			return (-1);//could be changed to continue maybe
		p = p->next;
	}
	p = start;
	while (p)
	{
		if (open_input_files_loop(p) < 0)
			return (-1);//reserved for critical errors
		p = p->next;
	}
	return (1);
}

int	rep_output_redir(t_pipex *p)
{
	while (p)
	{
		open_outfiles_loop(p);
		p = p->next;
	}
	return (1);
}

int	rep_redir(t_pipex *p)
{
	if (!p)
		return (-1);
	if (rep_input_redir(p) < 0)
		return (-1);
	if (rep_output_redir(p) < 0)
		return (-1);
	return (1);
}