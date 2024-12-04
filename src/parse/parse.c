/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:19:37 by senayat           #+#    #+#             */
/*   Updated: 2024/11/01 19:16:48 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	parse_tokens(t_token *tokens, t_tree **tree)
{
	if (!tokens || !tree)
		return (false);
	if (tokens->type == TOK_END)
		return (true);
	if (tokens->type == TOK_PIPE)
		return (parse_handle_pipe(tokens, tree));
	else if (tokens->type == TOK_REDIR_IN || tokens->type == TOK_HEREDOC
		|| tokens->type == TOK_REDIR_OUT || tokens->type == TOK_APPEND)
		return (parse_handle_redirs(tokens, tree));
	else if (tokens->type == TOK_LIT_STR)
		return (parse_handle_strs(tokens, tree));
	else if (tokens->type == TOK_END)
		return (true);
	else
		return (parse_error(tree, -1, NULL));
	return (true);
}
