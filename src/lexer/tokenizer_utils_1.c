/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:12:48 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/25 03:28:48 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

char	*append_char_to_token(char *line, char c)
{
	int		i;
	int		len;
	char	*dest;

	if (c == '\0')
		return (line);
	i = 0;
	dest = NULL;
	if (line != NULL)
		len = ft_strlen(line);
	else
		len = 0;
	dest = malloc(sizeof(char) * (len + 2));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = line[i];
		i++;
	}
	dest[i] = c;
	dest[i + 1] = '\0';
	return (dest);
}

t_token	*save_token(char *line, char *value, int state)
{
	t_token	*token;

	token = data()->tokens;
	while (token != NULL)
		token = token->next;
	token = init_t_token();
	if (!token)
		return (NULL);
	token->value = value;
	if (*line == DOLLAR)
		token->expansion = true;
	else
		token->expansion = false;
	if (check_operators(*line) && state == 0)
		token->type = OPERATOR;
	else
		token->type = TOKEN;
	if (state == DQUOTE)
		token->split = false;
	else
		token->split = true;
	return (token);
}
