#include "../../minishell.h"

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

int	rep_input_redir(t_pipex *p)
{
	while (p)
	{
		check_if_doc_final(p);
		if (do_docs_loop(p) < 0)
			return (-1);//could be changed to continue maybe
		if (open_input_files_loop(p) < 0)
			return (-1);//reserved for critical errors
		p = p->next;
	}
	return (1);
}

void	app_outfile_opener(char *str, t_pipex *p)
{
	if (!str)
		return ;
	if (!*str)
	{
		ft_put_str_fd("invalid outfile\n", 2);
		mini_call()->exit_status = 1;
		p->bad_command = true;
		return ;
	}
	p->out_fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (p->out_fd == -1)
	{
		write (2, "minishell: ", 11);
		perror(str);
		mini_call()->exit_status = 1;
		p->bad_command = true;
		return ;
	}
}

void	std_outfile_opener(char *str, t_pipex *p)
{
	if (!str)
		return ;
	if (!*str)
	{
		ft_put_str_fd("invalid outfile\n", 2);
		mini_call()->exit_status = 1;
		p->bad_command = true;
		return ;
	}
	p->out_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->out_fd == -1)
	{
		write (2, "minishell: ", 11);
		perror(str);
		mini_call()->exit_status = 1;
		p->bad_command = true;
		return ;
	}
}

void	open_outfiles_loop(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p->red_out)
		return ;
	while (p->red_out[i] != NULL)
	{
		if (!ft_strncmp(p->red_out[i], "STD:", 4))
			std_outfile_opener(p->red_out[i] + 4, p);
		else if (!ft_strncmp(p->red_out[i], "APP:", 4))
			app_outfile_opener(p->red_out[i] + 4, p);
		if (p->bad_command == true)
			break ;
		i++;
	}
}


int	rep_output_redir(t_pipex *p)
{
	if (!p->red_out)
		return (0);
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