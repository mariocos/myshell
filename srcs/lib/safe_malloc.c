#include "../minishel.h"

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
		return (NULL);
	}
	return (ret);
}