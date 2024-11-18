#include "minishell.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*return_str;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	return_str = NULL;
	while (buffer[fd][0] || read(fd, buffer[fd], BUFFER_SIZE) > 0)
	{
		return_str = ft_special_join(return_str, buffer[fd]);
		if (return_str == NULL)
			return (NULL);
		if (return_str && return_str[ft_linelen(return_str)] == '\n')
			return (return_str);
	}
	return (return_str);
}

int	ft_linelen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

void	ft_buffer_shift_left(char *buffer, int move_size)
{
	int	i;

	i = 0;
	while (buffer[move_size])
		buffer[i++] = buffer[move_size++];
	while (i < BUFFER_SIZE)
		buffer[i++] = '\0';
}

char	*ft_special_join(char *str, char *buffer)
{
	char	*ret_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (buffer[0] == '\0' && (!str || str[0] == '\0'))
		return (NULL);
	ret_str = malloc(ft_strlen(str) + ft_linelen(buffer) + 2);
	if (!ret_str)
	{
		free(str);
		return (NULL);
	}
	while (str && str[j] != '\0')
	{
		ret_str[i++] = str[j++];
	}
	j = 0;
	while (buffer[j] && buffer[j - 1] != '\n')
		ret_str[i++] = buffer[j++];
	ret_str[i] = '\0';
	free(str);
	ft_buffer_shift_left(buffer, j);
	return (ret_str);
}
