/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:30:39 by kfergani          #+#    #+#             */
/*   Updated: 2022/10/25 18:22:44 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_token	*tokens)
{
	t_token	*prev;

	if (!tokens)
		return ;
	prev = tokens;
	tokens = tokens->next;
	while (tokens)
	{
		free(prev->value);
		free(prev);
		prev = tokens;
		tokens = tokens->next;
	}
	free(prev->value);
	free(prev);
}

void	free_args(t_args *args)
{
	t_args	*prev;

	if (!args)
		return ;
	prev = args;
	args = args->next;
	while (args)
	{
		free(prev->value);
		free(prev);
		prev = args;
		args = args->next;
	}
	free(prev->value);
	free(prev);
}

void	free_infile(t_infiles *infile)
{
	t_infiles	*prev;

	if (!infile)
		return ;
	prev = infile;
	infile = infile->next;
	while (infile)
	{
		free(prev);
		prev = infile;
		infile = infile->next;
	}
	free(prev);
}

void	free_outfile(t_outfiles *outfile)
{
	t_outfiles	*prev;

	if (!outfile)
		return ;
	prev = outfile;
	outfile = outfile->next;
	while (outfile)
	{
		free(prev);
		prev = outfile;
		outfile = outfile->next;
	}
	free(prev);
}

void	free_cmds(t_simple_cmd *cmd)
{
	t_simple_cmd	*prev;

	if (!cmd)
		return ;
	prev = cmd;
	cmd = cmd->next;
	while (cmd)
	{
		free_args(prev->args);
		free_infile(prev->infile);
		free_outfile(prev->outfile);
		free(prev->cmd);
		free(prev);
		prev = cmd;
		cmd = cmd->next;
	}
	free_args(prev->args);
	free_infile(prev->infile);
	free_outfile(prev->outfile);
	free(prev->cmd);
	free(prev);
}
