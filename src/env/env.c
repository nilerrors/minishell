/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:22:09 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 20:41:28 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	total_env(t_env *env)
{
	if (!env)
		return (0);
	return (1 + total_env(env->next));
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	int		i;
	t_env	*current;

	envp = ft_calloc(total_env(env) + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	current = env;
	while (current)
	{
		envp[i++] = ft_strjoin(
				ft_strdup(ft_strjoin(current->var, "=")), current->val);
		current = current->next;
	}
	return (envp);
}
