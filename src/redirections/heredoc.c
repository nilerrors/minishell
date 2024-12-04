/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:38:27 by senayat           #+#    #+#             */
/*   Updated: 2024/11/04 09:38:22 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	get_heredoc_child_child(t_msh *sh, char *end, int pipefd[2])
{
	char	*heredoc_content;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipefd[0]);
	heredoc_content = get_heredoc_content(sh, end);
	if (heredoc_content)
	{
		write(pipefd[1], heredoc_content, strlen(heredoc_content));
		free(heredoc_content);
	}
	close(pipefd[1]);
	exit_msh(sh, 0);
}

static char	*get_heredoc_child(t_msh *sh, char *end, int pipefd[2], int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return (NULL);
	}
	if (pid == 0)
		get_heredoc_child_child(sh, end, pipefd);
	close(pipefd[1]);
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		sh->exit_code = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
	{
		sh->exit_code = 128 + WTERMSIG(*status);
		close(pipefd[0]);
		return (NULL);
	}
	return ("success");
}

char	*get_heredoc(t_msh *sh, char *end)
{
	int		pipefd[2];
	int		status;
	char	*heredoc;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (NULL);
	}
	if (!get_heredoc_child(sh, end, pipefd, &status))
		return (NULL);
	heredoc = get_next_line(pipefd[0]);
	while (heredoc)
	{
		if (!sh->heredoc)
			sh->heredoc = ft_strdup("");
		sh->heredoc = ft_strjoin_free(sh->heredoc, heredoc);
		heredoc = get_next_line(pipefd[0]);
	}
	close(pipefd[0]);
	return (sh->heredoc);
}
