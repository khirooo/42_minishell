/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:14:12 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/26 02:18:50 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(int argc)
{
	if (argc == 1)
	{
		print_env_or_export("env", NULL);
		return (0);
	}
	return (1);
}

char	*ft_getenv(char *name)
{
	t_env_list	*tmp_env;

	tmp_env = ft_getenv_list(name);
	if (tmp_env && tmp_env->value)
		return (ft_strdup(tmp_env->value));
	return (ft_strdup(""));
}
