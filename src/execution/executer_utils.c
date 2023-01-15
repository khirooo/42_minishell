/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:36:32 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/30 20:28:50 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_len(t_simple_cmd *simple_cmd, int mode)
{
	int		len;
	t_args	*args;

	len = 0;
	args = simple_cmd->args;
	while (args)
	{
		if (!args->space || !mode)
			len++;
		args = args->next;
	}
	return (len);
}

int	init_args(t_simple_cmd *simple_cmd, char ***p_arg_array, int mode)
{
	int		i;
	int		len;
	t_args	*args;

	i = 0;
	len = arg_len(simple_cmd, mode);
	*p_arg_array = malloc(sizeof(char *) * (len + 1));
	if (*p_arg_array == NULL)
		return (4);
	(*p_arg_array)[len] = NULL;
	args = simple_cmd->args;
	while (i < len)
	{
		if (!args->space || !mode)
		{
			(*p_arg_array)[i] = args->value;
			i++;
		}
		args = args->next;
	}
	return (len);
}

void	creat_path(char *cmd, char ***path)
{
	if (*path)
		free(*path);
	*path = malloc(sizeof(char *) * 2);
	(*path)[0] = ft_strdup(cmd);
	(*path)[1] = NULL;
}

char	**ft_getpath(char *cmd)
{
	int		i;
	char	*keypair;
	char	**path;

	keypair = ft_getenv("PATH");
	path = ft_split(keypair, ':');
	free(keypair);
	i = 0;
	if (path == NULL || access(cmd, F_OK | X_OK) == 0 || ft_strchr(cmd, '/'))
		creat_path(cmd, &path);
	else
	{
		while (path && path[i])
		{
			path[i] = ft_strjoin2(ft_strjoin2(path[i], "/", 1), cmd, 1);
			i++;
		}
	}
	return (path);
}

int	check_cmds(char	*cmd)
{
	int			i;
	int			res;
	char		**path;
	struct stat	path_stat;

	i = 0;
	res = 2;
	path = ft_getpath(cmd);
	while (path && path[i])
	{
		stat(path[i], &path_stat);
		if (!S_ISDIR(path_stat.st_mode) && access(path[i], F_OK | X_OK) == 0)
		{
			res = 0;
			break ;
		}
		i++;
	}
	if (path != NULL)
		free_dp(path);
	return (res + S_ISDIR(path_stat.st_mode));
}
