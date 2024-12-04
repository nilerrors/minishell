/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:08:26 by senayat           #+#    #+#             */
/*   Updated: 2024/11/04 09:32:04 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_file(t_msh *sh, char *path)
{
	int		i;
	char	**bin_dirs;
	char	*exe_path;

	if (is_file(path))
		return (ft_strdup(path));
	if (!get_env_var_raw(sh, "PATH"))
		return (NULL);
	i = 0;
	bin_dirs = ft_split(get_env_var_raw(sh, "PATH"), ':');
	if (!bin_dirs)
		return (NULL);
	while (bin_dirs[i])
	{
		exe_path = path_join(bin_dirs[i++], path);
		if (!exe_path || is_file(exe_path))
			ft_free_tab((void **)bin_dirs);
		if (!exe_path)
			return (NULL);
		if (is_executable(exe_path))
			return (exe_path);
		free(exe_path);
	}
	ft_free_tab((void **)bin_dirs);
	return (NULL);
}

char	**command_args_to_tab(t_arg *arg)
{
	t_arg	*tmp;
	int		len;
	int		i;
	char	**tab;

	len = 0;
	tmp = arg;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	tab = ft_calloc(len + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tab[i] = ft_strdup(arg->arg);
		if (!tab[i])
			return ((char **)ft_free_tab((void **)tab));
		arg = arg->next;
		i++;
	}
	return (tab);
}
