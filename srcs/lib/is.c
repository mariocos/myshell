#include "../minishel.h"

int	ft_isspace(char c)
{
	if (c == 32 || (c <= 13 && c >= 9))
		return (1);
	return (0);
}
