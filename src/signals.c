/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:44:42 by senayat           #+#    #+#             */
/*   Updated: 2024/11/01 18:45:28 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sighandler_int(int sig)
{
	signal(SIGINT, SIG_IGN);
	(void)sig;
	ft_printf("\n");
	if (!g_minish_exec)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	signal(SIGINT, sighandler_int);
}

void	sighandler_quit(int sig)
{
	signal(SIGQUIT, SIG_IGN);
	(void)sig;
	if (g_minish_exec)
		ft_printf("\n");
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	signal(SIGQUIT, sighandler_quit);
}
