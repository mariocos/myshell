#include "../minishell.h"

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
	return (ret);
}
