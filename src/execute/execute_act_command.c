/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_act_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:21:06 by senayat           #+#    #+#             */
/*   Updated: 2024/11/04 09:36:45 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	execute_act_normal_command_child(t_msh *sh, t_tree *tree)
{
	char	*cmd;
	char	*bin;
	char	**args;

	cmd = tree->arg.command.args->arg;
	args = command_args_to_tab(tree->arg.command.args);
	if (is_directory(cmd) || (is_file(cmd) && !is_executable(cmd)))
	{
		sh->exit_code = 126;
		if (is_directory(cmd))
			ft_printerr("minishell: %s: Is a directory\n", cmd);
		else
			ft_printerr("minishell: %s: Permission denied\n", cmd);
		exit_msh(sh, sh->exit_code);
	}
	bin = find_file(sh, cmd);
	if (!bin || execve(bin, args, env_to_envp(sh->env)) == -1)
	{
		free(bin);
		ft_free_tab((void **)args);
		sh->exit_code = 127;
		ft_printerr("command not found: %s\n", cmd);
		exit_msh(sh, sh->exit_code);
	}
}

static bool	execute_act_normal_command(t_msh *sh, t_tree *tree)
{
	int		status;

	sh->pid = fork();
	if (sh->pid == -1)
		return (false);
	if (sh->pid == 0)
		execute_act_normal_command_child(sh, tree);
	waitpid(sh->pid, &status, 0);
	if (WIFEXITED(status))
		sh->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		sh->exit_code = 128 + WTERMSIG(status);
	else
		sh->exit_code = -1;
	return (true);
}

bool	execute_act_command(t_msh *sh, t_tree *tree)
{
	int		save_stdin;
	int		save_stdout;

	if ((tree->arg.command.in || tree->arg.command.out)
		&& !handle_redirections(sh,
			&tree->arg.command, &save_stdin, &save_stdout))
		return (false);
	if (!tree->arg.command.args || !tree->arg.command.args->arg)
	{
		if (tree->arg.command.in || tree->arg.command.out)
			restore_redirections(save_stdin, save_stdout);
		return (true);
	}
	g_minish_exec = true;
	if (is_builtin(tree->arg.command.args->arg))
		execute_builtin(sh, tree->arg.command.args->arg,
			command_args_to_tab(tree->arg.command.args));
	else
		execute_act_normal_command(sh, tree);
	if (tree->arg.command.in || tree->arg.command.out)
		restore_redirections(save_stdin, save_stdout);
	g_minish_exec = false;
	return (true);
}
