/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd_and_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:12:58 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/12/09 21:41:02 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(int fd)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (wd != NULL)
	{
		write(fd, wd, ft_strlen(wd));
		write(fd, "\n", 1);
		free(wd);
		mini_call()->exit_status = 0;
	}
	else
	{
		error_message("minishell: pwd", fd);
		mini_call()->exit_status = 1;
	}
}

void	error_message(char *msg, int fd)
{
	char	*error;

	if (msg && *msg)
	{
		write (fd, msg, ft_strlen(msg));\
		write (fd, ": ", 2);
	}
	if (errno != 0)
	{
		error = strerror(errno);
		write (fd, error, ft_strlen(error));
	}
	write (fd, "\n", 1);
}

void	cd(const char *new_dir, int fd)
{
	char	env_var[4128];
	char	wd[4096];

	if ((!ft_strncmp(new_dir, "~/", ft_strlen("~/"))
			&& ft_strlen(new_dir) == ft_strlen("~/"))
		|| (new_dir[0] == '~' && !new_dir[1]))
		new_dir = getenv("HOME");
	if (chdir(new_dir))
	{
		error_message("minishell: cd", fd);
		mini_call()->exit_status = 1;
		return ;
	}
	if (getcwd(wd, sizeof(wd)) == NULL)
	{
		error_message("minishell: pwd: ", fd);
		mini_call()->exit_status = 1;
		return ;
	}
	ft_strlcpy(env_var, "PWD=", sizeof(env_var));
	ft_strlcat(env_var, wd, sizeof(env_var));
	export((char *[]){"export", env_var, NULL}, fd);
	mini_call()->exit_status = 0;
}

static bool	check_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

void	echo(char **cmd, int fd)
{
	int		i;
	bool	flag;

	i = 1;
	flag = false;
	if (cmd[1] && check_flag(cmd[1]))
	{
		flag = true;
		i++;
	}
	while(cmd[i] && check_flag(cmd[i]))
		i++;
	while (cmd[i])
	{
		write (fd, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1] != NULL)
			write (fd, " ", 1);
		i++;
	}
	if (!flag)
			write (fd, "\n", 1);
	mini_call()->exit_status = 0;
}
