/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:04:52 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/30 05:10:50 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_io_mod(int type)
{
	if (type == LESS || type == LESS_LESS
		|| type == GREATER || type == GREATER_GREATER)
		return (true);
	return (false);
}

int	init_cmd_struct(t_simple_cmd **simple_cmd)
{
	*simple_cmd = malloc(sizeof(t_simple_cmd));
	if (*simple_cmd == NULL)
		return (2);
	(*simple_cmd)->cmd = NULL;
	(*simple_cmd)->args = NULL;
	(*simple_cmd)->next = NULL;
	(*simple_cmd)->infile = NULL;
	(*simple_cmd)->outfile = NULL;
	(*simple_cmd)->heredocs = NULL;
	(*simple_cmd)->err_code = 0;
	(*simple_cmd)->error = false;
	return (0);
}

int	add_args(t_args **args, char *value, int space)
{
	while (*args != NULL)
		args = &(*args)->next;
	*args = malloc(sizeof(t_args));
	if (*args == NULL)
		return (2);
	(*args)->space = 0;
	if (space == SPACE)
		(*args)->space = 1;
	(*args)->value = value;
	(*args)->next = NULL;
	return (0);
}

void	ft_handel_in(t_simple_cmd *cmd, t_token *token, int last_op)
{
	t_token	*tmp;

	if (token->next && token->next->type != SPACE
		&& !is_io_mod(token->next->type)
		&& token->next->type != PIPE)
	{
		token->value = ft_strjoin2(token->value, token->next->value, 1);
		if (token->quot != -1 || token->next->quot != -1)
			token->quot = '"';
		tmp = token->next;
		token->next = token->next->next;
		free(tmp->value);
		free(tmp);
	}
	if (add_infiles(&(cmd->infile), token->value, last_op, token->quot) != 0)
		token->error = true;
}

t_token	*get_next_word(t_token *token)
{
	if (!token)
		return (NULL);
	token = token->next;
	while (token && token->type != WORD && token->type != PIPE)
		token = token->next;
	return (token);
}
