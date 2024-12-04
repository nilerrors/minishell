/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_interpolate_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:45:13 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 17:45:22 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	str_interpolate_var(t_msh *sh, char **s, char *str)
{
	char	*var;
	char	*tmp;

	var = take_variablename(str);
	if (!var)
		return (-1);
	str += ft_strlen(var);
	tmp = get_env_var(sh, var);
	free(var);
	if (!tmp)
		return (0);
	*s = ft_strjoin_free(*s, tmp);
	tmp = *s;
	*s = ft_strjoin(tmp, str);
	free(tmp);
	return (1);
}
