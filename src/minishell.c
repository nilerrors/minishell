/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:26:46 by senayat           #+#    #+#             */
/*   Updated: 2024/09/13 22:09:15 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sighandler_int(int sig)
{
	signal(SIGINT, SIG_IGN);
	(void)sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal(SIGINT, sighandler_int);
}

void	sighandler_quit(int sig)
{
	signal(SIGQUIT, SIG_IGN);
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal(SIGQUIT, sighandler_quit);
}

int	main(int ac, char **av, char **envp)
{
	t_msh	sh;

	(void)ac;
	(void)av;
	signal(SIGINT, sighandler_int);
	signal(SIGQUIT, sighandler_quit);
	sh.envp = envp;
	sh.exit_code = 0;
	sh.line = NULL;
	while (!sh.should_exit)
	{
		sh.line = readline("minishell> ");
		if (!sh.line)
			break;
		if (*sh.line)
			add_history(sh.line);
		handle_line(&sh);
		free(sh.line);
		sh.line = NULL;
	}
	return (0);
}
