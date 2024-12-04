/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:42:17 by senayat           #+#    #+#             */
/*   Updated: 2024/11/01 19:16:36 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	free_tokens(int status, t_token **token)
{
	t_token	*cur_tok;

	if (!token)
		return (0);
	cur_tok = *token;
	if (cur_tok)
	{
		free(cur_tok->literal);
		if (cur_tok->next)
			free_tokens(status, &cur_tok->next);
		free(cur_tok);
	}
	*token = NULL;
	return (status);
}

int	display_tokenization_error_and_free(int status, t_token **token)
{
	if (status == -1)
		ft_puts(1, "Allocation error: malloc failed\n");
	if (status == -2)
		ft_puts(1, "Tokenization error: unclosed string\n");
	return (free_tokens(status, token));
}

bool	merge_literals_together(t_token **token)
{
	t_token	*cur_tok;
	t_token	*next_tok;

	if (!token || !*token || !(*token)->next)
		return (false);
	cur_tok = *token;
	next_tok = cur_tok->next;
	if ((cur_tok->type == TOK_LIT_STR || cur_tok->type == TOK_STR
			|| cur_tok->type == TOK_NORMAL) && (next_tok->type == TOK_LIT_STR
			|| next_tok->type == TOK_STR || next_tok->type == TOK_NORMAL))
	{
		cur_tok->literal = ft_strjoin_free(cur_tok->literal, next_tok->literal);
		cur_tok->next = cur_tok->next->next;
		free(next_tok);
	}
	else
	{
		cur_tok = next_tok;
	}
	merge_literals_together(&cur_tok);
	return (true);
}

bool	cleanse_tokens(t_token **token)
{
	t_token	*cur_tok;

	if (!token || !*token)
		return (false);
	if ((*token)->type == TOK_SPC_CHR
		|| ((*token)->type == TOK_NORMAL
			&& (!(*token)->literal || !*(*token)->literal)))
	{
		cur_tok = (*token);
		*token = (*token)->next;
		if (cur_tok->literal)
			free(cur_tok->literal);
		free(cur_tok);
		cleanse_tokens(token);
	}
	else
	{
		if ((*token)->type == TOK_NORMAL || (*token)->type == TOK_STR)
			(*token)->type = TOK_LIT_STR;
		cleanse_tokens(&(*token)->next);
	}
	return (true);
}
