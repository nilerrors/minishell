/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:26:46 by senayat           #+#    #+#             */
/*   Updated: 2024/11/08 09:10:26 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	g_minish_exec;

static char	*prompt(t_msh *sh)
{
	if (sh->exit_code == 0)
		return (GREEN"→ "NORMAL"minishell> ");
	return (RED"→ "NORMAL"minishell> ");
}

static bool	handle_shell_line(t_msh *sh)
{
	if (!sh)
		return (false);
	free_msh_not_env(sh);
	sh->line = readline(prompt(sh));
	if (!sh->line)
		return (false);
	if (!isempty_line(sh->line))
	{
		add_history(sh->line);
		if (!handle_line(sh))
			sh->exit_code = 127;
	}
	else
		sh->exit_code = 0;
	free(sh->line);
	sh->line = NULL;
	return (true);
}

int	main(int ac, char **av, char **envp)
{
	t_msh	sh;

	(void)ac;
	(void)av;
	signal(SIGINT, sighandler_int);
	signal(SIGQUIT, sighandler_quit);
	ft_bzero(&sh, sizeof(t_msh));
	g_minish_exec = false;
	if (!init_env_var(&sh.env, envp))
	{
		free_msh(&sh);
		return (1);
	}
	while (!sh.should_exit)
		if (!handle_shell_line(&sh))
			break ;
	ft_printf("exit\n");
	return (0);
}
