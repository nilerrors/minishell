/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:19:39 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 19:51:34 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	print_args(t_msh *sh, char **args, int i)
{
	bool	space;

	if (!sh || !args || i < 0)
		return (false);
	space = false;
	while (args[i])
	{
		if (space)
			ft_printf(" ");
		ft_printf("%s", args[i++]);
		space = true;
	}
	return (true);
}

bool	execute_echo(t_msh *sh, char **args)
{
	int		i;
	bool	new_line;

	if (!sh)
		return (false);
	sh->exit_code = 0;
	new_line = true;
	i = 1;
	while (args[i])
	{
		if (ft_strncmp(args[i], "-n", 3) != 0)
			break ;
		new_line = false;
		i++;
	}
	print_args(sh, args, i);
	if (new_line)
		ft_printf("\n");
	return (true);
}
