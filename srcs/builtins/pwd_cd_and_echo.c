/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd_and_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:12:58 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/12/05 15:51:47 by hugo-mar         ###   ########.fr       */
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
		perror("minishell: pwd: ");
		mini_call()->exit_status = 1;
	}
}

void	cd(const char *new_dir, t_env *env)
{
	char	env_var[4128];
	char	wd[4096];

	if ((!ft_strncmp(new_dir, "~/", ft_strlen("~/"))
			&& ft_strlen(new_dir) == ft_strlen("~/"))
		|| (new_dir[0] == '~' && !new_dir[1]))
		new_dir = getenv("HOME");
	if (chdir(new_dir))
	{
		perror("minishell: cd");
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
	export(env_var, env, true);
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
