#include "../../../minishell.h"

static int	open_input_file(char *str, t_pipex *p)
{
	p->in_fd = open(str, O_RDONLY);
	if (p->in_fd == -1)
	{
		write (2, "minishell: ", 11);
		perror(str);
		p->bad_command = true;
		p->in_fd = 0;
		return (-1);
	}
	return (1);
}

int	open_input_files_loop(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p->red_in)
		return (0);
	while (p->red_in[i] != NULL)
	{
		if (!ft_strncmp(p->red_in[i], "STD:", 4) && !p->bad_command)
			if (open_input_file(p->red_in[i] + 4, p) < 0)
				break ;
		i++;
	}
	if (p->has_doc)
		if_close(p->in_fd);
	return (1);
}