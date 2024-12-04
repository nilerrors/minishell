/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 21:41:54 by senayat           #+#    #+#             */
/*   Updated: 2024/09/24 11:44:41 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	tokenize(char *s, t_token **token)
{
	int	n;

	if (!s)
		return (0);
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (0);
	(*token)->type = END;
	(*token)->literal = NULL;
	(*token)->next = NULL;
	n = 0;
	if (!*s)
		return (1);
	if (*s == ' ')
	{
		n = 1;
		(*token)->type = SPC_CHR;
		(*token)->literal = NULL;
	}
	else if (*s == '\'' || *s == '"')
	{
		(*token)->type = LIT_STR;
		if (*s == '"')
			(*token)->type = STR;
		n = feed_until_next(s, &(*token)->literal);
	}
	else if (*s == '>')
	{
		n = 1;
		(*token)->type = REDIR_OUT;
		(*token)->literal = NULL;
		if (*(s + 1) && *(s + 1) == '>')
		{
			(*token)->type = APPEND;
			n++;
		}
	}
	else if (*s == '<')
	{
		n = 1;
		(*token)->type = REDIR_IN;
		(*token)->literal = NULL;
		if (*(s + 1) && *(s + 1) == '<')
		{
			(*token)->type = HEREDOC;
			n++;
		}
	}
	else if (*s == '|')
	{
		n = 1;
		(*token)->type = PIPE;
		(*token)->literal = NULL;
	}
	else
	{
		(*token)->type = STR;
		n = feed_until_enduqstr(s, &(*token)->literal);
	}
	if (n <= 0)
		return (n);
	return (tokenize(s + n, &(*token)->next));
}

int	free_tokens(int status, t_token **token)
{
	t_token *cur_tok;

	if (!token)
		return (0);
	cur_tok = *token;
	if (cur_tok)
	{
		free(cur_tok->literal);
		if (cur_tok->next)
			free_tokens(status, &cur_tok->next);
	}
	*token = NULL;
	return (status);
}

int display_tokenization_error_and_free(int status, t_token **token)
{
	if (status == -1)
		ft_puts(1, "Allocation error: malloc failed\n");
	if (status == -2)
		ft_puts(1, "Tokenization error: unclosed string\n");
	return (free_tokens(status, token));
}

void display_tokens(t_token *token)
{
	while (token)
	{
		switch (token->type)
		{
			case SPC_CHR:
				printf("Token: [Type: SPC_CHR, Literal: \"%s\"]\n", token->literal);
				break;
			case LIT_STR:
				printf("Token: [Type: LIT_STR, Literal: \"%s\"]\n", token->literal);
				break;
			case STR:
				printf("Token: [Type: STR, Literal: \"%s\"]\n", token->literal);
				break;
			case REDIR_IN:
				printf("Token: [Type: <]\n");
				break;
			case REDIR_OUT:
				printf("Token: [Type: >]\n");
				break;
			case HEREDOC:
				printf("Token: [Type: <<]\n");
				break;
			case APPEND:
				printf("Token: [Type: >>]\n");
				break;
			case PIPE:
				printf("Token: [Type: |]\n");
				break;
			case END:
				printf("Token: [Type: END]\n");
				break;
			default:
				printf("Not yet added: Other\n");
				break;
		}
		token = token->next;
	}
}

bool	handle_line(t_msh *sh)
{
	int		status;
	t_token	*token;

	if (!sh || !sh->line || !sh->envp)
		return (false);
	status = 0;
	status = tokenize(sh->line, &token);
	if (status < 0)
		return (display_tokenization_error_and_free(status, &token));
	display_tokens(token);
	return (free_tokens(status, &token));
}
