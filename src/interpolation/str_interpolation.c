/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_interpolation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:46:00 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 17:46:17 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	str_interpolation(t_msh *sh, char **s)
{
	char	*os;
	char	*str;
	int		interpolated;

	if (!sh || !s || !*s)
		return (false);
	os = *s;
	str = *s;
	if (!ft_char_in_str('$', str))
		return (true);
	if ((ft_strchr(str, '$') - str) < 0)
		return (false);
	*s = (char *)ft_calloc((ft_strchr(str, '$') - str) + 1, sizeof(char));
	if (!*s)
		return (false);
	memcpy(*s, str, (ft_strchr(str, '$') - str));
	str += (ft_strchr(str, '$') - str);
	str++;
	interpolated = str_interpolate_var(sh, s, str);
	if (interpolated == -1)
		free(os);
	if (interpolated <= 0)
		return (false);
	return (true);
}
