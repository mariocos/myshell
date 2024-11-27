#include "../minishell.h"

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = s;
	while (i < n)
	{
		*ptr = c;
		i++;
		ptr++;
	}
	return (s);
}

/*
to be fully implemented but should signal that there was a critical error
and sanitize and exit on error
*/
void	*safe_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
	{
//		free_all();
//		safe_exit();
		printf("\nA CRITICAL ERROR HAS OCCURRED\n\n");
		return (NULL);
	}
	ft_memset(ret, '\0', size);
	return (ret);
}
