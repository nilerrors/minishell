/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feed.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:44:47 by senayat           #+#    #+#             */
/*   Updated: 2024/11/01 19:15:03 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	feed_until_next(char *s, char **into)
{
	char	c;
	int		i;
	int		n;

	if (!s || !*s)
		return (-1);
	c = *s;
	i = 0;
	s++;
	while (s[i] && s[i] != c)
		i++;
	if (!s[i])
		return (-2);
	n = i + 1;
	*into = malloc(sizeof(char) * (n));
	if (!*into)
		return (-1);
	(*into)[i] = '\0';
	while (i > 0)
	{
		i--;
		(*into)[i] = s[i];
	}
	return (n + 1);
}

int	feed_until_enduqstr(char *s, char **into)
{
	int		i;
	int		n;

	if (!s || !*s)
		return (-1);
	i = 0;
	while (s[i] && s[i] != '\''
		&& s[i] != '"' && s[i] != ' '
		&& s[i] != '>' && s[i] != '<'
		&& s[i] != '|')
		i++;
	n = i + 1;
	*into = malloc(sizeof(char) * (n));
	if (!*into)
		return (-1);
	(*into)[i] = '\0';
	while (i > 0)
	{
		i--;
		(*into)[i] = s[i];
	}
	return (n - 1);
}
