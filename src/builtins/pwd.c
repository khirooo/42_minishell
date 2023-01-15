/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:14:36 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/26 06:43:59 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*path;
	int		ret;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ret = err_handle(1, "pwd: ", path);
		free(path);
		return (ret);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
