/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:19:19 by senayat           #+#    #+#             */
/*   Updated: 2024/11/02 17:47:13 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	interpolate_into_strs(t_msh *sh, t_token **token)
{
	t_token	*cur_tok;

	if (!sh || !token)
		return (false);
	cur_tok = *token;
	if (!cur_tok)
		return (false);
	if (cur_tok->type == TOK_HEREDOC && cur_tok->next
		&& (cur_tok->next->type == TOK_STR
			|| cur_tok->next->type == TOK_NORMAL))
	{
		if (cur_tok->next->next)
			interpolate_into_strs(sh, &cur_tok->next->next);
		return (true);
	}
	else if (cur_tok->type == TOK_STR || cur_tok->type == TOK_NORMAL)
	{
		while (ft_char_in_str('$', cur_tok->literal))
			str_interpolation(sh, &cur_tok->literal);
	}
	if (cur_tok->next)
		interpolate_into_strs(sh, &cur_tok->next);
	return (true);
}
