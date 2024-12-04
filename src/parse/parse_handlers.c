/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:55:29 by senayat           #+#    #+#             */
/*   Updated: 2024/11/01 19:17:00 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	parse_handle_pipe(t_token *tokens, t_tree **tree)
{
	t_tree		*t;

	if (tokens->type != TOK_PIPE)
		return (parse_error(tree, -5, NULL));
	if (!tokens->next || tokens->next->type == TOK_END
		|| tokens->next->type == TOK_PIPE)
		return (parse_error(tree, -3, NULL));
	if (!(*tree))
		return (parse_error(tree, -2, NULL));
	t = ft_calloc(1, sizeof(t_tree));
	if (!t)
		return (parse_error(tree, -1, NULL));
	t->action = ACT_PIPE;
	t->arg.pipe.first = *tree;
	if (!parse_tokens(tokens->next, &t->arg.pipe.second))
		free_tree(&t);
	*tree = t;
	return (true);
}

static bool	parse_handle_redirin(t_token *tokens, t_tree **tree)
{
	t_redirin	**in;

	if (tokens->type != TOK_REDIR_IN && tokens->type != TOK_HEREDOC)
		return (parse_error(tree, -5, NULL));
	in = &(*tree)->arg.command.in;
	while (*in)
		in = &(*in)->next;
	*in = ft_calloc(1, sizeof(t_redirin));
	if (!*in)
		return (parse_error(tree, -1, NULL));
	(*in)->heredoc = tokens->type == TOK_HEREDOC;
	(*in)->arg = ft_strdup(tokens->next->literal);
	(*in)->next = NULL;
	return (parse_tokens(tokens->next->next, tree));
}

static bool	parse_handle_redirout(t_token *tokens, t_tree **tree)
{
	t_redirout	**out;

	if (tokens->type != TOK_REDIR_OUT && tokens->type != TOK_APPEND)
		return (parse_error(tree, -5, NULL));
	out = &(*tree)->arg.command.out;
	while (*out)
		out = &(*out)->next;
	*out = ft_calloc(1, sizeof(t_redirout));
	if (!*out)
		return (parse_error(tree, -1, NULL));
	(*out)->append = tokens->type == TOK_APPEND;
	(*out)->file = ft_strdup(tokens->next->literal);
	(*out)->next = NULL;
	return (parse_tokens(tokens->next->next, tree));
}

bool	parse_handle_redirs(t_token *tokens, t_tree **tree)
{
	if (tokens->type != TOK_REDIR_IN && tokens->type != TOK_HEREDOC
		&& tokens->type != TOK_REDIR_OUT && tokens->type != TOK_APPEND)
		return (parse_error(tree, -5, NULL));
	if (!tokens->next || tokens->next->type != TOK_LIT_STR)
		return (parse_error(tree, -4, tokens));
	if (!(*tree))
	{
		*tree = ft_calloc(1, sizeof(t_tree));
		if (!*tree)
			return (parse_error(tree, -1, NULL));
		(*tree)->action = ACT_COMMAND;
	}
	if ((*tree)->action != ACT_COMMAND)
		return (parse_error(tree, -5, NULL));
	if (tokens->type == TOK_REDIR_IN || tokens->type == TOK_HEREDOC)
		return (parse_handle_redirin(tokens, tree));
	else if (tokens->type == TOK_REDIR_OUT || tokens->type == TOK_APPEND)
		return (parse_handle_redirout(tokens, tree));
	return (parse_error(tree, -5, NULL));
}

bool	parse_handle_strs(t_token *tokens, t_tree **tree)
{
	t_arg		**arg;

	if (tokens->type != TOK_LIT_STR)
		return (parse_error(tree, -5, NULL));
	if (!(*tree))
	{
		*tree = ft_calloc(1, sizeof(t_tree));
		if (!*tree)
			return (parse_error(tree, -1, NULL));
		(*tree)->action = ACT_COMMAND;
	}
	arg = &(*tree)->arg.command.args;
	while (*arg)
		arg = &(*arg)->next;
	*arg = ft_calloc(1, sizeof(t_arg));
	if (!*arg)
		return (parse_error(tree, -1, NULL));
	(*arg)->next = NULL;
	(*arg)->arg = ft_strdup(tokens->literal);
	if (!(*arg)->arg)
		return (parse_error(tree, -1, NULL));
	return (parse_tokens(tokens->next, tree));
}
