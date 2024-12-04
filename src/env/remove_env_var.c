/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:41:09 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 20:41:19 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	remove_env_var(t_msh *sh, char *var)
{
	t_env	**current;
	t_env	*to_delete;

	if (!sh)
		return (false);
	current = &(sh->env);
	while (*current && strcmp((*current)->var, var) != 0)
		current = &((*current)->next);
	if (*current)
	{
		to_delete = *current;
		*current = (*current)->next;
		free(to_delete);
	}
	return (true);
}
