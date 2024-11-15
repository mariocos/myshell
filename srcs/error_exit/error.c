#include "../minishel.h"

void	ft_perror(char *err_msg)
{
	int	i;

	i = 0;
	while (err_msg[i] != '\0')
	{
		write(1, &err_msg[i], 1);//made this instead of putstr so i can change where the err_msg goes to
	}
}

void	syntax_error(void)
{
	printf("\na syntax error has ocurred :(\n\n");
}