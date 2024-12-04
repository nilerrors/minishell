/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:15:54 by senayat           #+#    #+#             */
/*   Updated: 2024/11/08 09:11:15 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	free_msh(t_msh *sh)
{
	if (!sh)
		return (false);
	free_tree(&(sh->tree));
	deinit_env_var(&(sh->env));
	free_tokens(1, &(sh->token));
	return (true);
}

bool	free_msh_not_env(t_msh *sh)
{
	if (!sh)
		return (false);
	free_tree(&(sh->tree));
	free_tokens(1, &(sh->token));
	return (true);
}

bool	exit_msh(t_msh *sh, int code)
{
	free_msh(sh);
	exit(code);
}

bool	execute_exit(t_msh *sh, char **args)
{
	if (!sh || !args)
		return (false);
	ft_printf("exit\n");
	if (!args[1])
		exit(0);
	if (!ft_isinteger(args[1], &sh->exit_code))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", *args);
		exit_msh(sh, 2);
	}
	if (args[2])
	{
		ft_printf("minishell: exit: too many arguments\n", *args);
		exit_msh(sh, 1);
	}
	exit_msh(sh, sh->exit_code);
	return (false);
}
