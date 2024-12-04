/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:41:37 by senayat           #+#    #+#             */
/*   Updated: 2024/11/01 19:14:50 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	redirinout_pipe(char *s, t_token **token, int *n)
{
	*n = 1;
	if (*s == '>')
	{
		(*token)->type = TOK_REDIR_OUT;
		if (*(s + 1) && *(s + 1) == '>')
		{
			(*token)->type = TOK_APPEND;
			(*n)++;
		}
	}
	else if (*s == '<')
	{
		(*token)->type = TOK_REDIR_IN;
		if (*(s + 1) && *(s + 1) == '<')
		{
			(*token)->type = TOK_HEREDOC;
			(*n)++;
		}
	}
	else if (*s == '|')
	{
		(*token)->type = TOK_PIPE;
	}
}

static void	special_tokens(char *s, t_token **token, int *n)
{
	if (*s == ' ')
	{
		*n = 1;
		(*token)->type = TOK_SPC_CHR;
	}
	else if (*s == '\'' || *s == '"')
	{
		(*token)->type = TOK_LIT_STR;
		if (*s == '"')
			(*token)->type = TOK_STR;
		*n = feed_until_next(s, &(*token)->literal);
	}
	else if (*s == '>' || *s == '<' || *s == '|')
		redirinout_pipe(s, token, n);
}

int	tokenize(char *s, t_token **token)
{
	int	n;

	if (!s)
		return (0);
	*token = ft_calloc(1, sizeof(t_token));
	if (!*token)
		return (0);
	(*token)->type = TOK_END;
	n = 0;
	if (!*s)
		return (1);
	if (*s == ' ' || *s == '\'' || *s == '"' || *s == '>'
		|| *s == '<' || *s == '|')
		special_tokens(s, token, &n);
	else
	{
		(*token)->type = TOK_NORMAL;
		n = feed_until_enduqstr(s, &(*token)->literal);
	}
	if (n <= 0)
		return (n);
	return (tokenize(s + n, &(*token)->next));
}
