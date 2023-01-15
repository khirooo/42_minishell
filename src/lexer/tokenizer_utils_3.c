/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:55:14 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/27 04:23:33 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_dq_token(char	**input, int *flag)
{
	t_token	*token;
	int		i;

	*flag = 1;
	token = init_t_token();
	if (!token)
		return (NULL);
	token->expansion = 1;
	token->quot = '"';
	i = 0;
	while (*(*input + i + 1) && *(*input + i + 1) != '"')
		i++;
	if (i)
		token->value = ft_substr(*input, *flag, i, 0);
	else
	{
		while (*(*input + i) && is_space(*(*input + i)))
			i++;
		if (i)
			token->value = ft_strdup(" ");
		else
			token->value = ft_strdup("");
	}
	*input = ft_substr(*input, i + 2, ft_strlen(*input) - i, 1);
	return (token);
}

t_token	*get_sq_token(char	**input, int *flag)
{
	t_token	*token;
	int		i;

	*flag = 1;
	i = 0;
	token = init_t_token();
	if (!token)
		return (NULL);
	token->quot = '\'';
	while (*(*input + i + 1) && *(*input + i + 1) != '\'')
		i++;
	if (i)
		token->value = ft_substr(*input, 1, i, 0);
	else
	{
		while (*(*input + i) && is_space(*(*input + i)))
			i++;
		if (i)
			token->value = ft_strdup(" ");
		else
			token->value = ft_strdup("");
	}
	*input = ft_substr(*input, i + 2, ft_strlen(*input) - i, 1);
	return (token);
}

t_token	*get_redir_token(char **input)
{
	t_token	*token;

	token = init_t_token();
	if (!token)
		return (NULL);
	token->type = 0;
	token->expansion = 1;
	if (**input == '>' || **input == '<')
		while (*(*input + token->type) == **input && token->type < 2)
			token->type++;
	else if (**input == '|')
			token->type++;
	if (token->type)
		token->value = ft_substr(*input, 0, token->type, 0);
	else
	{
		while (*(*input + token->type) && is_space(*(*input + token->type)))
			token->type++;
		if (token->type)
			token->value = ft_strdup(" ");
		else
			token->value = ft_strdup("");
	}
	*input = ft_substr(*input, token->type, ft_strlen(*input) - token->type, 1);
	return (token);
}

t_token	*init_t_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = NULL;
	token->type = 0;
	token->next = NULL;
	token->split = false;
	token->error = false;
	token->err_code = 0;
	token->expansion = 0;
	token->quot = -1;
	return (token);
}
