/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:14:00 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/27 00:51:06 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_flag(char *arg)
{
	if (*arg != '-')
		return (false);
	arg++;
	if (!*arg)
		return (false);
	while (*arg)
	{
		if (*arg != 'n')
			return (false);
		arg++;
	}
	return (true);
}

void	echo_print(bool n_flag, char **argv)
{
	while (*argv)
	{
		printf("%s", *argv);
		argv++;
	}
	if (!n_flag)
		printf("\n");
}

int	ft_echo(int argc, char **argv)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	if (argc == 1)
	{
		printf("\n");
		return (0);
	}
	while (argv[i] && check_flag(argv[i]))
		i++;
	if (i > 1)
		n_flag = true;
	echo_print(n_flag, &(argv[i]));
	return (0);
}
