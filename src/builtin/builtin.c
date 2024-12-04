/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:51:58 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 18:21:17 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	execute_builtin(t_msh *sh, char *cmd, char **args)
{
	bool	status;

	if (ft_strncmp(cmd, "exit", 5) == 0)
		status = true;
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		status = execute_pwd(sh, args);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		status = execute_env(sh, args);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		status = execute_chdir(sh, args);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		status = execute_echo(sh, args);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		status = execute_export(sh, args);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		status = execute_unset(sh, args);
	ft_free_tab((void **)args);
	return (status);
}
