/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:37:08 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/21 17:43:06 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fds(int fd[4])
{
	fd[STDIN_INIT] = dup(STDIN_FILENO);
	fd[STDOUT_INIT] = dup(STDOUT_FILENO);
	fd[IN] = dup(fd[STDIN_INIT]);
	fd[OUT] = dup(fd[STDOUT_INIT]);
}

void	reset_fds(int fd[4])
{
	close(fd[IN]);
	close(fd[OUT]);
	dup2(fd[STDIN_INIT], STDIN_FILENO);
	dup2(fd[STDOUT_INIT], STDOUT_FILENO);
	close(fd[STDIN_INIT]);
	close(fd[STDOUT_INIT]);
}
