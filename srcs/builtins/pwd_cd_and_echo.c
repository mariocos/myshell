/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd_and_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:12:58 by hugo-mar          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/12 14:56:22 by hugo-mar         ###   ########.fr       */
=======
/*   Updated: 2024/11/18 13:27:12 by mariocos         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(void) // Também pode ser retirada da env
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (wd != NULL)
	{
		printf("%s\n", wd);
		free(wd);
	}
	else
		perror("bash: pwd: ");
}

// Ainda há a situação do "~/any/dir" - "~/" tem de ser tratado como expansion
void	cd(const char *new_dir, t_env *env) // Sem update OLDPWD (não é pedido)
{
	char	env_var[4128];
	char	wd[4096];

	if ((!ft_strncmp(new_dir, "~/", ft_strlen("~/"))
			&& ft_strlen(new_dir) == ft_strlen("~/"))
		|| (new_dir[0] == '~' && !new_dir[1]))
		new_dir = getenv("HOME");
	if (chdir(new_dir))
	{
		perror("bash: cd: ");
		return ;
	}
	if (getcwd(wd, sizeof(wd)) == NULL)
	{
		perror("bash: pwd: ");
		return ;
	}
	ft_strlcpy(env_var, "PWD=", sizeof(env_var));
	ft_strlcat(env_var, wd, sizeof(env_var));
	export(env_var, env, true);
}

static bool	check_flag(char *str)
{
	int	i;

	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (true);
	}
	return (false);
}

void	echo(char **args)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	if (args[0] && check_flag(args[0]))
	{
		flag = true;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
}
