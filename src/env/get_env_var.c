/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:38:46 by senayat           #+#    #+#             */
/*   Updated: 2024/11/04 09:31:51 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_var(t_msh *sh, char *s)
{
	t_env	*current;

	if (!sh)
		return (NULL);
	if (!s)
		return (ft_strdup(""));
	if (*s == '?' && *(s + 1) == '\0')
		return (ft_itoa(sh->exit_code));
	current = sh->env;
	while (current)
	{
		if (ft_strncmp(current->var, s, ft_strlen(s)) == 0)
			return (ft_strdup(current->val));
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*get_env_var_raw(t_msh *sh, char *s)
{
	t_env	*current;

	if (!sh)
		return (NULL);
	if (!s)
		return ("");
	if (*s == '?' && *(s + 1) == '\0')
		return (ft_itoa(sh->exit_code));
	current = sh->env;
	while (current)
	{
		if (ft_strncmp(current->var, s, ft_strlen(s)) == 0)
			return (current->val);
		current = current->next;
	}
	return ("");
}
