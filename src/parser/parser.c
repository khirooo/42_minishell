/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:16:02 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/30 18:13:59 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redir(t_simple_cmd *cmd, t_token *token)
{
	int	last_op;

	last_op = 0;
	while (token != NULL && token->type != PIPE)
	{
		if (is_io_mod(token->type))
			last_op = token->type;
		if (token->type == REDIR)
		{
			if (last_op == LESS || last_op == LESS_LESS)
				ft_handel_in(cmd, token, last_op);
			else if (last_op == GREATER || last_op == GREATER_GREATER)
				add_outfiles(&(cmd->outfile), token->value, last_op);
			last_op = 0;
		}
		token = token->next;
	}
	return (0);
}

void	set_cmd_err(t_simple_cmd *simple_cmd, t_token *token)
{
	if (token->error)
	{
		simple_cmd->error = true;
		simple_cmd->err_code = token->err_code;
	}
}

void	ft_set_cmd(t_simple_cmd *simple_cmd, t_token *token)
{
	set_cmd_err(simple_cmd, token);
	if (token->type == WORD && simple_cmd->cmd == NULL)
	{
		simple_cmd->cmd = ft_strdup(token->value);
		set_cmd_err(simple_cmd, token);
	}
	if (token->type == WORD || (token->type == SPACE && simple_cmd->args
			&& simple_cmd->args->next && get_next_word(token)
			&& get_next_word(token)->type == WORD))
		add_args(&(simple_cmd->args),
			ft_strdup(token->value), token->type);
}

int	handel_invalid_cmd(t_simple_cmd *simple_cmd)
{
	if (simple_cmd->cmd && (!*simple_cmd->cmd \
		|| !ft_strcmp(simple_cmd->cmd, "..") \
		|| !ft_strcmp(simple_cmd->cmd, ".")))
	{
		data()->cmds->error = true;
		data()->cmds->err_code = 1;
		data()->exit_state = 127;
		return (1);
	}
	return (0);
}

int	parse(void)
{
	t_token			*token;
	t_simple_cmd	*simple_cmd;

	token = data()->tokens;
	init_cmd_struct(&(data()->cmds));
	simple_cmd = data()->cmds;
	while (token && !parse_redir(simple_cmd, token))
	{
		while (token && token->type != PIPE)
		{
			ft_set_cmd(simple_cmd, token);
			token = token->next;
		}
		if (token && token->type == PIPE)
			set_cmd_err(simple_cmd, token);
		if (handel_invalid_cmd(simple_cmd))
			return (err_handle(1, simple_cmd->cmd, ": "));
		if (!token)
			break ;
		init_cmd_struct(&(simple_cmd->next));
		simple_cmd = simple_cmd->next;
		token = token->next;
	}
	return (0);
}
