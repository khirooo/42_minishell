/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:35:43 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/30 05:54:14 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bashify_exit_status(void)
{
	if (data()->exit_state == 127)
		return (data()->exit_state);
	if (data()->exit_state == 2)
		return (data()->exit_state);
	if (data()->exit_state == 258)
		return (data()->exit_state = 258);
	if (data()->exit_state == 2)
		return (data()->exit_state = 130);
	if (data()->exit_state >= 256)
		data()->exit_state >>= 8;
	return (data()->exit_state);
}

void	get_pid_array(pid_t **pid_array)
{
	t_simple_cmd	*cmd;
	int				i;

	i = 0;
	cmd = data()->cmds;
	while (cmd && cmd->cmd)
	{
		if (!is_builtin(cmd->cmd) && !cmd->error)
			i++;
		cmd = cmd->next;
	}
	*pid_array = malloc(i * sizeof(pid_t));
}

void	execute(pid_t **id_array, t_simple_cmd *simple_cmd, int fd[4], int *i)
{
	while (simple_cmd != NULL)
	{
		if (simple_cmd->err_code == 4 || simple_cmd->err_code == 5
			|| simple_cmd->err_code == 6)
			break ;
		if (!simple_cmd->error && simple_cmd->cmd)
		{
			if (!is_builtin(simple_cmd->cmd))
				(*id_array)[(*i)++] = exec_cmd(simple_cmd, fd);
			else
				exec_cmd(simple_cmd, fd);
		}
		simple_cmd = simple_cmd->next;
	}
}

int	xecute(void)
{
	int				fd[4];
	t_simple_cmd	*simple_cmd;
	int				i;
	pid_t			*id_array;

	i = 0;
	get_pid_array(&id_array);
	simple_cmd = data()->cmds;
	if (simple_cmd != NULL)
		init_fds(fd);
	else
		return (2);
	execute(&id_array, simple_cmd, fd, &i);
	reset_fds(fd);
	while (i >= 0)
	{
		waitpid(id_array[i], &data()->exit_state, 0);
		i--;
	}
	return (bashify_exit_status());
}

// int	xecute(void)
// {
// 	int				fd[4];
// 	t_simple_cmd	*simple_cmd;
// 	int				i;

// 	i = 0;
// 	simple_cmd = data()->cmds;
// 	if (simple_cmd != NULL)
// 		init_fds(fd);
// 	else
// 		return (2);
// 	while (simple_cmd != NULL && ++i)
// 	{
// 		if (simple_cmd->err_code == 4 || simple_cmd->err_code == 5
// 			|| simple_cmd->err_code == 6)
// 			break ;
// 		if (!simple_cmd->error && simple_cmd->cmd)
// 			exec_cmd(simple_cmd, fd);
// 		simple_cmd = simple_cmd->next;
// 	}
// 	reset_fds(fd);
// 	while (i--)
// 		wait(&data()->exit_state);
// 	return (bashify_exit_status());
// }
