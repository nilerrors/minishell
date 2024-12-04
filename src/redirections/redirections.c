/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:12:01 by senayat           #+#    #+#             */
/*   Updated: 2024/11/03 21:21:36 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	handle_redirections_in_heredoc(t_msh *sh, t_redirin *in)
{
	int			pipefd[2];

	sh->heredoc = get_heredoc(sh, in->arg);
	if (!sh->heredoc)
		return (ft_printf("minishell: warning: here-document delimited"
				"by end-of-file (wanted `%s')\n", in->arg) && false);
	if (pipe(pipefd) == -1)
	{
		perror("minishell: pipe");
		return (false);
	}
	write(pipefd[1], sh->heredoc, ft_strlen(sh->heredoc));
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(pipefd[0]);
		return (false);
	}
	close(pipefd[0]);
	free(sh->heredoc);
	sh->heredoc = NULL;
	return (true);
}

static bool	handle_redirections_in(t_msh *sh, t_redirin *in)
{
	t_fd		fd;

	while (in)
	{
		if (!in->heredoc)
		{
			fd = open(in->arg, O_RDONLY);
			if (fd == -1)
			{
				perror("minishell: input redirection failed");
				return (false);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("minishell: dup2");
				close(fd);
				return (false);
			}
			close(fd);
		}
		else if (!handle_redirections_in_heredoc(sh, in))
			return (false);
		in = in->next;
	}
	return (true);
}

static bool	handle_redirections_out(t_redirout *out)
{
	t_fd		fd;

	if (out->append)
		fd = open(out->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: output redirection failed");
		return (false);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (false);
	}
	close(fd);
	out = out->next;
	return (true);
}

bool	handle_redirections(t_msh *sh,
		t_command *cmd, int *save_stdin, int *save_stdout)
{
	if (!cmd || !save_stdin || !save_stdout)
		return (false);
	*save_stdin = dup(STDIN_FILENO);
	*save_stdout = dup(STDOUT_FILENO);
	if (*save_stdin == -1 || *save_stdout == -1)
		return (ft_printerr("minishell: failed to save std-in/out") && false);
	if (!handle_redirections_in(sh, cmd->in))
		return (false);
	if (!handle_redirections_out(cmd->out))
		return (false);
	return (true);
}

void	restore_redirections(int save_stdin, int save_stdout)
{
	if (dup2(save_stdin, STDIN_FILENO) == -1)
		printf("minishell: failed to restore stdin");
	if (dup2(save_stdout, STDOUT_FILENO) == -1)
		printf("minishell: failed to restore stdout");
	close(save_stdin);
	close(save_stdout);
}
