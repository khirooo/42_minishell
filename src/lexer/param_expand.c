/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:27:43 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/26 18:46:06 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	paramlen(char *param)
{
	int	len;

	len = 0;
	if (param[len] == QMARK)
		return (1);
	if (param[len] != '_' && !ft_isalpha(param[len]))
		return (0);
	while (param[len] == '_' || ft_isalnum(param[len]))
		len++;
	return (len);
}

char	*expand_single(char *value, int var_pos, char *var)
{
	char	*before;
	char	*before_mid;
	char	*after;
	char	*tmp;
	int		len;

	len = paramlen(var + 1);
	var = ft_substr(var, 1, len, 0);
	if (*var == QMARK)
		tmp = ft_itoa(data()->exit_state);
	else
		tmp = ft_strdup(ft_getenv(var));
	free(var);
	var = tmp;
	before = ft_substr(value, 0, var_pos, 0);
	after = ft_substr(value, var_pos + len + 1,
			ft_strlen(value) - var_pos - len - 1, 0);
	before_mid = ft_strjoin_withnull(before, var, 1);
	var = ft_strjoin_withnull(before_mid, after, 1);
	free(after);
	return (var);
}

void	param_expand(void)
{
	t_token	*token;
	char	*var;
	int		var_pos;

	token = data()->tokens;
	while (token)
	{
		var = ft_strchr(token->value, DOLLAR);
		var_pos = ft_strchr_pos(token->value, DOLLAR);
		if (var && paramlen(var + 1) != 0 && token->expansion)
			token->value = expand_single(token->value, var_pos, var);
		if (!token->expansion || !ft_strchr(token->value, DOLLAR)
			|| paramlen(ft_strchr(token->value, DOLLAR) + 1) == 0)
			token = token->next;
	}
	tokenize_operators();
	del_empty_tokens();
	fusion();
}
