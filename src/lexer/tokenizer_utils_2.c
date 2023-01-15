/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:53:08 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/25 17:54:29 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_state(char line)
{
	int	*state;

	state = &data()->state;
	if (line == DQUOTE && *state == DQUOTE)
			*state = 0;
	else if (line == DQUOTE && *state == 0)
			*state = DQUOTE;
	if (line == SQUOTE && *state == SQUOTE)
			*state = 0;
	else if (line == SQUOTE && *state == 0)
		*state = SQUOTE;
	return (*state);
}

bool	check_spaces(char c)
{
	if (c == SPACE || c == TAB || c == NEWLINE)
		return (true);
	return (false);
}

bool	check_operators(char c)
{
	if (c == LESS || c == GREATER || c == PIPE)
		return (true);
	return (false);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_is_token_dlmtr(char c)
{
	if (!is_space(c) && c != '|' && c != '>'
		&& c != '<' && c != '"' && c != '\'')
		return (0);
	return (1);
}
