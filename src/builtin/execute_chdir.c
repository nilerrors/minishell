/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_chdir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:17:54 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 19:47:55 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	change_dir(t_msh *sh, char *dir, char *path)
{
	getcwd(dir, PATH_MAX);
	set_env_var(sh, "OLDPWD", ft_strdup(dir));
	if (chdir(path) != 0)
	{
		sh->exit_code = 1;
		ft_printerr("cd: %s\n", strerror(errno));
		return (false);
	}
	else
		set_env_var(sh, "PWD", ft_strdup(getcwd(dir, PATH_MAX)));
	return (true);
}

bool	execute_chdir(t_msh *sh, char **args)
{
	char	dir[PATH_MAX];
	char	*path;

	if (!sh || !args)
		return (false);
	sh->exit_code = 0;
	if (args[1] && args[2])
	{
		ft_printerr("cd: too many arguments\n");
		sh->exit_code = 1;
		return (false);
	}
	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
		path = get_env_var(sh, "HOME");
	else if (ft_strncmp(args[1], "-", 2) == 0)
		path = get_env_var(sh, "OLDPWD");
	else
		path = ft_strdup(args[1]);
	if (!path)
		return (false);
	return (change_dir(sh, dir, path));
}
