/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:26:20 by senayat           #+#    #+#             */
/*   Updated: 2024/09/24 11:43:15 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"

# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_toktype
{
	ILLEGAL,
	SPC_CHR,
	STR,
	LIT_STR,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	PIPE,
	END,
}	t_toktype;

typedef struct s_token
{
	t_toktype		type;
	char			*literal;
	struct s_token	*next;
}	t_token;

typedef struct s_msh
{
	bool	should_exit;
	bool	exit_code;
	t_int	in;
	t_int	out;
	t_int	pid;
	char	**envp;
	char	*line;
}	t_msh;

bool	handle_line(t_msh *sh);
int		tokenize(char *s, t_token **token);

#endif // MINISHELL_H
