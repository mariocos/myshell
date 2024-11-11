/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_and_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:12:58 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/11/11 12:57:02 by hugo-mar         ###   ########.fr       */
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
