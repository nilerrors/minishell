/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:52:57 by senayat           #+#    #+#             */
/*   Updated: 2024/11/01 19:17:10 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	free_current_give_next(t_ptr val, t_ptr *current)
{
	if (!current)
		return (false);
	free(*current);
	*current = val;
	return (true);
}

static bool	free_command(t_command *command)
{
	t_ptr	current;

	if (!command)
		return (false);
	current = command->args;
	while (current)
	{
		free(((t_arg *)current)->arg);
		free_current_give_next(((t_arg *)current)->next, &current);
	}
	current = command->in;
	while (current)
		free_current_give_next(((t_redirin *)current)->next, &current);
	current = command->out;
	while (current)
		free_current_give_next(((t_redirout *)current)->next, &current);
	command->args = NULL;
	command->in = NULL;
	command->out = NULL;
	return (true);
}

bool	free_tree(t_tree **tree)
{
	if (!tree)
		return (false);
	if (!*tree)
		return (true);
	if ((*tree)->action == ACT_COMMAND)
		free_command(&(*tree)->arg.command);
	else if ((*tree)->action == ACT_PIPE)
	{
		free_tree(&(*tree)->arg.pipe.first);
		free_tree(&(*tree)->arg.pipe.second);
	}
	ft_set_free((void **)tree);
	return (true);
}

bool	parse_error(t_tree **tree, int err, t_token *token)
{
	if (err == 0)
		return (true);
	if (err == -1)
		printf("Allocation error: malloc failed\n");
	else if (err == -2)
		printf("Syntax error: expected token before '|'\n");
	else if (err == -3)
		printf("Syntax error: expected token after '|'\n");
	else if (err == -4)
	{
		if (token->type == TOK_REDIR_IN)
			printf("Syntax error: expected token after '<'\n");
		else if (token->type == TOK_REDIR_OUT)
			printf("Syntax error: expected token after '>'\n");
		else if (token->type == TOK_HEREDOC)
			printf("Syntax error: expected token after '<<'\n");
		else if (token->type == TOK_APPEND)
			printf("Syntax error: expected token after '>>'\n");
	}
	else if (err == -5)
		printf("Logic error\n");
	else
		printf("Some other error\n");
	free_tree(tree);
	return (false);
}
