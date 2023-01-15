/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:07:05 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/27 04:23:13 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_user_input(char **buffer)
{
	if (!isatty(fileno(stdin)))
		*buffer = ft_strtrim(get_next_line(fileno(stdin)), "\n", 1);
	else
		*buffer = readline("> ");
}

bool	quotes_matched(char *line)
{
	char	*pipe;

	pipe = ft_strchr(line, PIPE);
	data()->state = 0;
	while (*line)
	{
		set_state(*line);
		line++;
	}
	if (set_state(*line) != 0 || (pipe && *(pipe + 1) == '\0'
			&& ft_strlen(line) > 1))
		return (false);
	return (true);
}

void	del_empty_tokens(void)
{
	t_token	*token;
	t_token	*tmp;

	token = data()->tokens;
	while (token)
	{
		if ((token->type == PIPE || is_io_mod(token->type)
				|| *token->value == '-') && token->next
			&& token->next->type == SPACE)
		{
			tmp = token->next;
			token->next = token->next->next;
			free(tmp->value);
			free(tmp);
		}
		token = token->next;
	}
}

void	fusion(void)
{
	t_token	*token;

	token = data()->tokens;
	while (token)
	{
		if ((token->type == WORD && *(token->value) != '-'
				&& token->next && token->next->type == WORD))
		{
			token->value = ft_strjoin2(token->value, token->next->value, 1);
			if (token->quot == '"' || token->next->quot == '\'')
				token->quot = '"';
			token->next = token->next->next;
		}
		else
			token = token->next;
	}
}

int	lexer(char *user_input)
{
	t_token	*token;
	char	*quoted;

	token = init_t_token();
	if (!token)
		exit(1);
	data()->state = 0;
	if (quotes_matched(user_input))
		user_input = ft_strtrim(user_input, "\n\t ", 1);
	while (!quotes_matched(user_input))
	{
		user_input = ft_strjoin2(user_input, "\n", 1);
		get_user_input(&quoted);
		if (quoted)
			user_input = ft_strjoin2(user_input, quoted, 1);
		else
			break ;
		free(quoted);
	}
	if (!*user_input)
		return (-1);
	data()->tokens = get_tokens(user_input);
	param_expand();
	return (check_syntax());
}
