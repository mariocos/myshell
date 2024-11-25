#include "../minishell.h"

/*
this file handles removing quotes from the pipex list things where it matters 
e.g.
*/

int	remove_quote_len(char *str)//working as intended
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = -1;
	if (len == 0)
		return (0);
	while (str[++i] != '\0')
	{
		if (ft_isquote(str[i]) > 0)
		{
			len -= 2;//take away the two quotes
			i += advance_quotes(str, i);
		}
	}
	return (len);
}

int	advance_quotes(char *str, int i)//working as intended
{
	int	len;

	len = i;
	if (str[len] == '"')
	{
		len++;
		while (str[len] != '"')
			len++;
		return (len + 1 - i);//adding one for the final quote 
	}
	else if (str[len] == '\'')
	{
		len++;
		while (str[len] != '\'')
			len++;
		return (len + 1 - i);
	}
	else
	{
		printf("error in parsing quotes dude\n");
		return (-1);
	}
}

static void	copy_quote(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (src[i] == '\'')
	{
		i++;
		while (src[i] != '\'')
			dest[j++] = src[i++];
	}
	else if (src[i] == '\"')
	{
		i++;
		while (src[i] != '\"')
			dest[j++] = src[i++];
	}
	else
		printf("using copy quote wrong\n");
}

char	*rem_quote(char *str)//working
{
	char	*ret;
	int	i;
	int	ret_i;

	i = -1;
	ret_i = 0;
	if ((int)ft_strlen(str) == remove_quote_len(str))
		return (str);
	ret = safe_malloc(remove_quote_len(str) + 1);
	if (remove_quote_len(str) == 0)
		ret[0] = '\0';
	else
	{
		while (str[++i] != '\0')
		{
			if (ft_isquote(str[i]) > 0)
			{
				copy_quote(ret + ret_i, str + i);
				ret_i += advance_quotes(str, i) - 2;
				i += advance_quotes(str, i);
			}
			else
				ret[ret_i++] = str[i];
		}
	}
	free(str);
	return (ret);
}

void	remove_pipex_quotes(t_pipex *p)
{
	int	i;

	i = -1;
	while (p)
	{
		while (p->cmd && p->cmd[++i] != NULL)
			p->cmd[i] = rem_quote(p->cmd[i]);
		i = -1;
		while (p->red_in && p->red_in[++i])
			p->red_in[i] = rem_quote(p->red_in[i]);
		i = -1;
		while (p->red_out && p->red_out[++i])
			p->red_out[i] = rem_quote(p->red_out[i]);
		p = p->next;
	}
}