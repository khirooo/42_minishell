/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:45:57 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/27 14:33:05 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_expand(char *line)
{
	char	*var;
	int		var_pos;
	char	*tmp;

	var = ft_strchr(line, DOLLAR);
	if (!var)
		return (line);
	var_pos = var - line;
	tmp = line;
	line = expand_single(line, var_pos, var);
	free(tmp);
	return (line);
}

int	creat_heredocs(char *dlmtr, int expantion, char *heredoc)
{
	int			fd;
	char		*line;

	line = NULL;
	fd = open(heredoc, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	data()->state = 2;
	get_user_input(&line);
	if (data()->state == 0 && close(fd) != 99)
		return (-1);
	while (line && ft_strcmp(line, dlmtr))
	{
		if (expantion != '"' && expantion != '\'')
			line = heredoc_expand(line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		get_user_input(&line);
	}
	if (line)
		free(line);
	close(fd);
	return (fd);
}

int	read_heredocs(char	*dlmtr, int expantion)
{
	int			fd;
	char		*heredoc;
	char		*tmp;

	data()->n_heredocs++;
	tmp = ft_itoa(data()->n_heredocs);
	heredoc = ft_strjoin2(tmp, "heredoc", 1);
	if (creat_heredocs(dlmtr, expantion, heredoc) == -1)
	{
		free(heredoc);
		return (-1);
	}
	free(heredoc);
	fd = open(heredoc, O_RDONLY);
	return (fd);
}

int	add_infiles(t_infiles **infile, char *file, int mode, int expantion)
{
	while (*infile != NULL)
		infile = &(*infile)->next;
	*infile = malloc(sizeof(t_infiles));
	(*infile)->next = NULL;
	if (*infile == NULL)
		return (2);
	if (mode == LESS)
	{
		(*infile)->value = open(file, O_RDONLY);
		if ((*infile)->value == -1)
		{
			err_handle(3, " ", ft_strjoin2(file, ": ", 0));
			data()->exit_state = 1;
			return (3);
		}
		(*infile)->dlmtr = NULL;
	}
	else if (mode == LESS_LESS)
		(*infile)->value = read_heredocs(file, expantion);
	(*infile)->next = NULL;
	return (0);
}

int	add_outfiles(t_outfiles **outfile, char *file, int mode)
{
	while (*outfile != NULL)
		outfile = &(*outfile)->next;
	*outfile = malloc(sizeof(t_outfiles));
	(*outfile)->next = NULL;
	if (*outfile == NULL)
		return (2);
	if (mode == GREATER)
		(*outfile)->value = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	else if (mode == GREATER_GREATER)
		(*outfile)->value = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	(*outfile)->next = NULL;
	return (0);
}
