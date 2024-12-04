/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_act_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:22:08 by senayat           #+#    #+#             */
/*   Updated: 2024/11/04 09:37:37 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	execute_act_pipe_child(t_msh *sh,
	t_tree *tree, int pipe_fd[2], pid_t *pid)
{
	int		pidnum;

	pidnum = *pid;
	*pid = fork();
	if (*pid == -1)
		return (ft_printerr("fork") && false);
	if (*pid == 0)
	{
		if (pidnum == 1)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			execute_command(sh, tree->arg.pipe.first);
			exit_msh(sh, sh->exit_code);
		}
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		execute_command(sh, tree->arg.pipe.second);
		exit_msh(sh, sh->exit_code);
	}
	return (true);
}

bool	execute_act_pipe(t_msh *sh, t_tree *tree)
{
	int		status;
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (false);
	}
	pid1 = 1;
	pid2 = 2;
	if (!execute_act_pipe_child(sh, tree, pipe_fd, &pid1)
		|| !execute_act_pipe_child(sh, tree, pipe_fd, &pid2))
		return (false);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	sh->exit_code = WEXITSTATUS(status);
	if (WIFEXITED(status))
		sh->exit_code = WEXITSTATUS(status);
	else
		sh->exit_code = -1;
	return (true);
}
