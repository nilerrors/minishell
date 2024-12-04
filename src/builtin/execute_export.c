/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:20:29 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 19:52:12 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	execute_export(t_msh *sh, char **args)
{
	int		i;
	t_env	*env;

	if (!sh || !args)
		return (false);
	sh->exit_code = 0;
	i = 1;
	if (!args[i])
		return (execute_env(sh, args));
	while (args[i])
	{
		if (!is_valid_env_var(args[i]))
		{
			ft_printerr("export: `%s`: not a valid identifier\n", args[i]);
			sh->exit_code = 1;
		}
		else
		{
			env = env_from_envstr(args[i]);
			set_env_var(sh, env->var, env->val);
			free(env);
		}
		i++;
	}
	return (true);
}
