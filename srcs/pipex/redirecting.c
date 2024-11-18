#include "../minishel.h"

void	get_out_fd(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p)
		return (-1);
	if (!p->red_out)
		return (0);
	while (p->red_out[i] != NULL)
	{
		if (!ft_strncmp(p->red_out[i], "STD:", 4))
			check_outfile(p->red_out[i]);
		else if (!ft_strncmp(p->red_out[i], "APP:", 4));
			check_outfile_app(p->red_out[i]);
		i++;
	}
	i--;
}