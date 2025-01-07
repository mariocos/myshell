/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd_and_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:12:58 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/07 12:27:14 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(int fd)
{
	char	*wd;

	wd = NULL;
	wd = getcwd(NULL, 0);
	if (!wd)
		wd = ft_strdup(mini_call()->pwd);
	if (wd != NULL)
	{
		write(fd, wd, ft_strlen(wd));
		write(fd, "\n", 1);
		free(wd);
		mini_call()->exit_status = 0;
	}
	else
	{
		perror("minishell: pwd");
		mini_call()->exit_status = 1;
	}
}

static void	update_pwd(void)
{
	char	*help;

	help = NULL;
	help = getcwd(NULL, 0);
	if (help)
	{
		free(mini_call()->pwd);
		mini_call()->pwd = help;
	}
}

void	cd(char **args, int fd)
{
	char	env_var[4128];
	char	wd[4096];

	if (!args[1] || (!ft_strncmp(args[1], "~/", ft_strlen("~/"))
			&& ft_strlen(args[1]) == ft_strlen("~/"))
		|| (args[1][0] == '~' && !args[1][1]))
		args[1] = get_var_value(mini_call()->env, "HOME");
	if (chdir(args[1]))
	{
		write(2, "minishell: cd: ", 15);
		perror(args[1]);
		mini_call()->exit_status = 1;
		return ;
	}
	if (getcwd(wd, sizeof(wd)) == NULL)
	{
		perror("minishell: pwd: ");
		mini_call()->exit_status = 1;
		return ;
	}
	ft_strlcpy(env_var, "PWD=", sizeof(env_var));
	ft_strlcat(env_var, wd, sizeof(env_var));
	update_pwd();
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
	while (cmd[i] && check_flag(cmd[i]))
		i++;
	while (cmd[i])
	{
		ft_put_str_fd(cmd[i], fd);
		if (cmd[i + 1] != NULL && ft_strlen(cmd[i]))
			write (fd, " ", 1);
		i++;
	}
	if (!flag)
		write (fd, "\n", 1);
	mini_call()->exit_status = 0;
}
