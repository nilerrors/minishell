/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 21:11:29 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 21:15:22 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	deinit_env_var(t_env **env)
{
	if (!env)
		return (false);
	if (!*env)
		return (true);
	deinit_env_var(&((*env)->next));
	ft_set_free((void **)&((*env)->var));
	ft_set_free((void **)&((*env)->val));
	ft_set_free((void **)env);
	return (true);
}
