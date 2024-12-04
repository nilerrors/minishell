/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:17:08 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 18:17:17 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	execute_pwd(t_msh *sh, char **args)
{
	char	dir[PATH_MAX];

	if (!sh)
		return (false);
	sh->exit_code = 0;
	(void)args;
	if (!getcwd(dir, PATH_MAX))
		return (false);
	ft_printf("%s\n", dir);
	return (true);
}
