/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_and_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:12:58 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/11/11 12:02:55 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

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

void	cd(const char *new_dir, t_env *env) // Sem update OLDPWD (não é pedido)
{
	char	env_var[4128];
	char	wd[4096];

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
