/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:10:21 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 20:45:26 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_directory(char *path)
{
	struct stat	filestat;

	if (!path)
		return (false);
	if (stat(path, &filestat) == -1)
		return (false);
	return (S_ISDIR(filestat.st_mode));
}

bool	is_file(char *path)
{
	if (!path)
		return (false);
	return (access(path, F_OK) != -1);
}

bool	is_executable(char *path)
{
	if (!path)
		return (false);
	return (access(path, X_OK) != -1);
}

bool	is_builtin(char *name)
{
	if (!name)
		return (false);
	return (ft_strncmp(name, "echo", 5) == 0
		|| ft_strncmp(name, "cd", 3) == 0
		|| ft_strncmp(name, "pwd", 4) == 0
		|| ft_strncmp(name, "export", 7) == 0
		|| ft_strncmp(name, "unset", 6) == 0
		|| ft_strncmp(name, "env", 4) == 0
		|| ft_strncmp(name, "exit", 5) == 0);
}

char	*path_join(char *path, char *sub)
{
	char	*temp;
	char	*full;

	if (!path || !sub)
		return (NULL);
	if (ft_strendswith(path, "/"))
		return (ft_strjoin(path, sub));
	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	full = ft_strjoin(temp, sub);
	free(temp);
	if (!full)
		return (NULL);
	return (full);
}
