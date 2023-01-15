/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:08:10 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/26 20:23:13 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_any_token(char **input)
{
	t_token	*token;
	int		i;

	token = init_t_token();
	if (!token)
		return (NULL);
	token->expansion = 1;
	i = 0;
	while (*(*input + i) && !ft_is_token_dlmtr(*(*input + i)))
		i++;
	if (i)
		token->value = ft_substr(*input, 0, i, 0);
	else
	{
		while (*(*input + i) && is_space(*(*input + i)))
			i++;
		if (i)
			token->value = ft_strdup(" ");
		else
			token->value = ft_strdup("");
	}
	*input = ft_substr(*input, i, ft_strlen(*input) - i, 1);
	return (token);
}

void	set_type(t_token *token, int flag)
{
	if (check_operators(*token->value))
		token->type = OPERATOR;
	else if (!ft_strcmp(token->value, " ") && !flag)
		token->type = SPACE;
	else
		token->type = TOKEN;
}

t_token	*create_next_token(char **input)
{
	t_token	*token;
	char	*copy;
	int		flag;

	if (!input || !*input || !**input)
		return (NULL);
	if (**input == '$' && (*(*input + 1) == '"' || *(*input + 1) == '\''))
	{
		copy = ft_strdup(*input + 1);
		free(*input);
		*input = copy;
	}
	flag = 0;
	if (**input == '"')
		token = get_dq_token(input, &flag);
	else if (**input == '\'')
		token = get_sq_token(input, &flag);
	else if (**input == '>' || **input == '<' || **input == '|')
		token = get_redir_token(input);
	else
		token = get_any_token(input);
	set_type(token, flag);
	return (token);
}

void	add_back(t_token **lst, t_token *new)
{
	t_token	*ptr;

	if (!lst || !new)
		return ;
	ptr = *lst;
	if (!ptr)
	{
		*lst = new;
		new -> next = NULL;
	}
	else
	{
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = new;
	}
}

t_token	*get_tokens(char *input)
{
	t_token		*tokens;
	t_token		*t;

	input = ft_strtrim(input, " \t\b\v\n", 1);
	t = create_next_token(&input);
	tokens = NULL;
	while (t != NULL)
	{
		add_back(&tokens, t);
		t = create_next_token(&input);
	}
	free(input);
	return (tokens);
}
