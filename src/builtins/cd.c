/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:13:49 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/26 22:12:42 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(int dir, char *path, char *oldpath)
{
	dir = chdir(path);
	if (dir == -1)
	{
		if (!ft_strcmp(path, "?"))
			err_handle(7, "cd: ", " : ");
		else
			err_handle(7, "cd: ", path);
		data()->exit_state = 1;
	}
	else
		add_env(ft_strdup("OLDPWD"), ft_strdup(oldpath));
}

int	ft_cd(int argc, char **argv)
{
	int			dir;
	char		*path;
	char		*oldpath;

	dir = 0;
	if (argc > 1)
		path = ft_strdup(argv[1]);
	else if (argc == 1)
		path = ft_strdup("~");
	oldpath = getcwd(NULL, 0);
	if (ft_strcmp(path, "~") == 0)
		path = ft_getenv("HOME");
	if (ft_strcmp(path, "-") == 0)
	{
		path = ft_getenv("OLDPWD");
		if (path)
			printf("%s\n", path);
	}
	if (path != NULL && *path)
		change_dir(dir, path, oldpath);
	free(path);
	free(oldpath);
	return (1);
}
