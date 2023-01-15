/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:36:48 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/30 02:58:27 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_next_token(t_token *token)
{
	if (!token)
		return (NULL);
	token = token->next;
	while (token && token->type == SPACE)
		token = token->next;
	return (token);
}

int	check_syntax_helper2(t_token *token, int mod)
{
	token->error = true;
	token->err_code = 5;
	ft_printf("minishell: syntax error near token `newline'\n");
	data()->exit_state = 258;
	if (mod == 1)
		return (data()->exit_state);
	else if (mod == 2)
		return (err_handle(4, " ", token->value));
	else
	{
		token->err_code = 4;
		return (err_handle(4, " ", token->value));
	}
}

static int	check_syntax_helper(void)
{
	int		args;
	t_token	*token;

	args = 0;
	token = data()->tokens;
	while (token && ++args)
	{
		if ((args == 1 && token->type != WORD && token->type != SPACE
				&& !is_redir(token)) || (args == 1 && !token->next
				&& token->type != WORD))
			return (check_syntax_helper2(token, 2));
		else if (token->type == PIPE && get_next_token(token)
			&& get_next_token(token)->type == PIPE)
			return (check_syntax_helper2(token, 3));
		token = token->next;
	}
	return (0);
}

int	check_syntax(void)
{
	t_token	*token;

	token = data()->tokens;
	check_syntax_helper();
	while (token)
	{
		if (is_redir(token) && ((get_next_token(token) \
			&& get_next_token(token)->type != REDIR) || !get_next_token(token)))
		{
			token->error = true;
			token->err_code = 6;
			data()->exit_state = 2;
			return (err_handle(6, " ", token->value));
		}
		else if ((is_redir(token) && get_next_token(token)
				&& is_redir(get_next_token(token))))
		{
			token->error = true;
			token->err_code = 4;
			return (err_handle(4, " ", token->value));
		}
		token = token->next;
	}
	return (0);
}
