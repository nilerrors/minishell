/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_from_envstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:39:58 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 20:42:17 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*env_from_envstr(char *s)
{
	t_env	*env;
	int		i;

	if (!s || !is_valid_env_var(s))
		return (NULL);
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	env->var = ft_calloc(i + 1, sizeof(char));
	if (!env->var)
		return (NULL);
	env->val = ft_calloc(ft_strlen(s + i + (s[i] == '=')) + 1, sizeof(char));
	if (!env->var)
		return (NULL);
	ft_memcpy(env->var, s, i);
	ft_memcpy(env->val, s + i + (s[i] == '='),
		ft_strlen(s + i + (s[i] == '=')));
	return (env);
}
