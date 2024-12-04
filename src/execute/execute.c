/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:54:01 by senayat           #+#    #+#             */
/*   Updated: 2024/11/04 09:16:08 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	execute_command(t_msh *sh, t_tree *tree)
{
	if (!tree)
		return (false);
	if (tree->action == ACT_COMMAND)
		return (execute_act_command(sh, tree));
	else if (tree->action == ACT_PIPE)
		return (execute_act_pipe(sh, tree));
	return (true);
}
