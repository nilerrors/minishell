/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:38:11 by senayat           #+#    #+#             */
/*   Updated: 2024/11/08 09:12:03 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	init_env_var(t_env **env, char **envp)
{
	char	*assign_pos;

	if (!env || !envp)
		return (false);
	if (!envp[0])
	{
		*env = NULL;
		return (true);
	}
	*env = ft_calloc(1, sizeof(t_env));
	if (!*env)
		return (false);
	assign_pos = ft_strchr(envp[0], '=');
	(*env)->var = ft_calloc(assign_pos - envp[0] + 2, sizeof(char));
	if (!(*env)->var)
		return (false);
	(*env)->val = ft_strdup(assign_pos + 1);
	if (!(*env)->val)
		return (false);
	ft_strlcat((*env)->var, envp[0], assign_pos - envp[0] + 1);
	return (init_env_var(&((*env)->next), &(envp[1])));
}
