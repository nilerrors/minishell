/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_variablename.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:11:09 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 16:11:24 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*take_variablename(char *s)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	if (!*s)
		return (NULL);
	if (*s == '?')
		return (ft_strdup("?"));
	if (!((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')))
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
				|| (s[i] >= '0' && s[i] <= '9')))
			break ;
		i++;
	}
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	ft_memcpy(str, s, i);
	return (str);
}
