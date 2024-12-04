/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:19:26 by senayat           #+#    #+#             */
/*   Updated: 2024/11/03 13:19:35 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*join_with_next_line(char **s, char *line)
{
	*s = ft_strjoin_free(*s, line);
	if (!*s)
		return (NULL);
	*s = ft_strjoin_free(*s, ft_strdup("\n"));
	if (!*s)
		return (NULL);
	return (*s);
}

char	*get_heredoc_content(t_msh *sh, char *end)
{
	char	*s;
	char	*line;

	s = ft_strdup("");
	if (!s)
		return (NULL);
	line = NULL;
	while (true)
	{
		line = readline("> ");
		if (!line)
		{
			ft_set_free((void **)&s);
			return (NULL);
		}
		if (ft_strncmp(line, end, ft_strlen(end) + 1) == 0)
		{
			free(line);
			break ;
		}
		join_with_next_line(&s, line);
	}
	while (ft_char_in_str('$', s))
		str_interpolation(sh, &s);
	return (s);
}
