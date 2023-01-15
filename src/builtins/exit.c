/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:14:21 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/27 18:22:58 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exit(void)
{
	if (isatty(fileno(stdin)))
		printf("exit\n");
}

int	ft_exit_helper(char **argv)
{
	int	i;

	i = 0;
	if (ft_isdigit(argv[1][i]) || argv[1][i] == '+' || argv[1][i] == '-')
		i++;
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i]))
		{
			print_exit();
			err_handle(5, "exit: ", "numeric argument required");
			return (255);
		}
		i++;
	}
	if (i == 0)
	{
		print_exit();
		err_handle(5, "exit: ", "numeric argument required");
		return (255);
	}
	return (0);
}

int	ft_exit(int argc, char **argv)
{
	if (argc > 2)
	{
		print_exit();
		write(2, "minishell: exit: too many arguments\n", 36);
		data()->exit_state = 1;
	}
	else if (argc >= 2)
	{
		if (ft_exit_helper(argv))
		{
			free(argv);
			free_all();
			exit (255);
		}
		print_exit();
		return (ft_atoi(argv[1]));
	}
	else
	{
		print_exit();
		return (data()->exit_state);
	}
	return (data()->exit_state);
}
