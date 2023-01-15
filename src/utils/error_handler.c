/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:09:28 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/30 06:10:55 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_err(char *format, char *s1, char *s2, char *s3)
{
	ft_printf(format, s1, s2, s3);
	return (0);
}

int	err_handle_helper(int error_code, char *prog, char *err_input, char *err[])
{
	if (error_code == 0)
		print_err("minishell: %s%s%s\n", prog, err_input, err[0]);
	else if (error_code == 1)
		print_err("minishell: %s%s%s\n", prog, err_input, err[1]);
	else if (error_code == 2)
		print_err("minishell: %s%s%s\n", prog, err_input, err[2]);
	else if (error_code == 3)
		print_err("minishell: %s%s%s\n", prog, err_input, err[3]);
	else if (error_code == 4 || error_code == 6)
		print_err("minishell: %s%s: `%s'\n", prog, err[4], err_input);
	else if (error_code == 5)
		print_err("minishell: %s%s: %s\n", prog, "", err_input);
	else if (error_code == 7)
		print_err("minishell: %s%s%s\n", prog, err_input, err[7]);
	else if (error_code == 8)
		print_err("minishell: %s%s %s\n", prog, err_input, err[8]);
	else
		print_err("minishell: %s%s %s\n", prog, err_input, "failed to execve!\n");
	return (error_code);
}

int	err_handle(int error_code, char *prog, char *error_input)
{
	char	*err[9];

	err[0] = " missing ]";
	err[1] = " command not found";
	err[2] = " not an valid identifier";
	err[3] = " No such file or directory";
	err[4] = " syntax error near unexpected token";
	err[5] = " syntax error near unexpected token 'newline'";
	err[6] = " syntax error near unexpected token";
	err[7] = " Not a directory";
	err[8] = " is a directory";
	return (err_handle_helper(error_code, prog, error_input, err));
}
