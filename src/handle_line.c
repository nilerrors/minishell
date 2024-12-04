/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 21:41:54 by senayat           #+#    #+#             */
/*   Updated: 2024/11/01 19:58:43 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	isempty_line(char *s)
{
	if (!s || !*s)
		return (true);
	while (*s)
	{
		if (*s != ' ')
			return (false);
		s++;
	}
	return (true);
}

bool	handle_line(t_msh *sh)
{
	int		status;

	if (!sh || !sh->line)
		return (false);
	status = tokenize(sh->line, &sh->token);
	if (status < 0)
		return (display_tokenization_error_and_free(status, &sh->token));
	interpolate_into_strs(sh, &sh->token);
	merge_literals_together(&sh->token);
	cleanse_tokens(&sh->token);
	if (sh->token->type == TOK_END)
		return (free_tokens(status, &sh->token) && true);
	parse_tokens(sh->token, &sh->tree);
	if (!sh->tree)
		return (free_tokens(status, &sh->token) && false);
	if (sh->tree->action == ACT_COMMAND
		&& ft_strncmp(sh->tree->arg.command.args->arg, "exit", 5) == 0)
		return (execute_exit(sh,
				command_args_to_tab(sh->tree->arg.command.args)));
	execute_command(sh, sh->tree);
	free_tokens(status, &sh->token);
	free_tree(&sh->tree);
	return (true);
}
