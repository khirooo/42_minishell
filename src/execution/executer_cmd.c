/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:48:52 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/30 20:09:05 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_infile(t_simple_cmd *simple_cmd, int fdin)
{
	char		*line;
	t_infiles	*infile;

	(void)line;
	infile = simple_cmd->infile;
	line = NULL;
	while (infile)
	{
		close(fdin);
		fdin = infile->value;
		if (fdin == -1)
			return (-1);
		infile = infile->next;
	}
	return (fdin);
}

int	get_outfile(t_simple_cmd *simple_cmd, int fd[4])
{
	int			fdpipe[2];
	t_outfiles	*outfile;

	outfile = simple_cmd->outfile;
	while (outfile && outfile->next)
		outfile = outfile->next;
	if (outfile)
		fd[OUT] = outfile->value;
	else if (simple_cmd->next == NULL)
		dup2(fd[STDOUT_INIT], fd[OUT]);
	if (simple_cmd->next != NULL)
	{
		if (pipe(fdpipe) == -1)
			return (4);
		fd[IN] = fdpipe[0];
		fd[OUT] = fdpipe[1];
	}
	if (outfile != NULL)
		dup2(outfile->value, STDOUT_FILENO);
	else
		dup2(fd[OUT], STDOUT_FILENO);
	close(fd[OUT]);
	return (0);
}

int	exec_cmd_helper(t_simple_cmd *simple_cmd, int fd[4], int *ret)
{
	*ret = 0;
	fd[IN] = get_infile(simple_cmd, fd[IN]);
	if (fd[IN] == -1 && close(fd[IN]) && close(fd[OUT]))
		return (2);
	dup2(fd[IN], STDIN_FILENO);
	close(fd[IN]);
	get_outfile(simple_cmd, fd);
	data()->state = 1;
	return (0);
}

int	exec_cmd(t_simple_cmd *simple_cmd, int fd[4])
{
	int	ret;

	if (exec_cmd_helper(simple_cmd, fd, &ret) == 2)
		return (2);
	if (is_builtin(simple_cmd->cmd) || (!ft_strcmp(simple_cmd->cmd, "export")
			&& simple_cmd->args->next))
		data()->exit_state = exec_builtin1(simple_cmd);
	else
	{
		ret = fork();
		if (ret == 0)
		{
			close(fd[IN]);
			if (is_builtin2(simple_cmd->cmd))
			{
				ret = exec_builtin2(simple_cmd);
				free_all();
				exit(ret);
			}
			else
				child_process(simple_cmd);
		}
	}
	return (ret);
}
