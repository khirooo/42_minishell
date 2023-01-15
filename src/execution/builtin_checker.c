/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:44:08 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/25 16:44:53 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char	*cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

bool	is_builtin2(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "pwd"))
		return (true);
	return (false);
}
