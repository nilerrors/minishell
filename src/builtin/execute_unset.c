/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:20:59 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 18:21:15 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	execute_unset(t_msh *sh, char **args)
{
	int		i;

	if (!sh || !args)
		return (false);
	sh->exit_code = 0;
	i = 1;
	while (args[i])
	{
		remove_env_var(sh, args[i]);
		i++;
	}
	return (true);
}
