/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:16:24 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 18:16:33 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	execute_env(t_msh *sh, char **args)
{
	t_env	*current;

	if (!sh || !args)
		return (false);
	if (args[1])
	{
		ft_printf("env: too many arguments\n");
		sh->exit_code = 1;
		return (false);
	}
	sh->exit_code = 0;
	current = sh->env;
	while (current)
	{
		ft_printf("%s=%s\n", current->var, current->val);
		current = current->next;
	}
	return (true);
}
