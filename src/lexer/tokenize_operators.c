/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:31:34 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/26 20:23:03 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_token *token)
{
	int	type;

	if (token)
	{
		type = token->type;
		if (type == LESS || type == LESS_LESS
			|| type == GREATER || type == GREATER_GREATER)
			return (true);
	}
	return (false);
}

void	tokenize_operators(void)
{
	t_token	*token;

	token = data()->tokens;
	while (token)
	{
		if (token && token->value && token->type == OPERATOR)
		{
			if (ft_strcmp(token->value, "<") == 0)
				token->type = LESS;
			else if (ft_strcmp(token->value, "<<") == 0)
				token->type = LESS_LESS;
			else if (ft_strcmp(token->value, ">") == 0)
				token->type = GREATER;
			else if (ft_strcmp(token->value, ">>") == 0)
				token->type = GREATER_GREATER;
			else if (ft_strcmp(token->value, "|") == 0)
				token->type = PIPE;
			if (is_redir(token) && get_next_token(token)
				&& get_next_token(token)->type == TOKEN)
				get_next_token(token)->type = REDIR;
		}
		else if (token->type != REDIR && token->type != SPACE)
			token->type = WORD;
		token = token->next;
	}
}
