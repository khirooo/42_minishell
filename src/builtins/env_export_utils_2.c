/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:25:53 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/30 02:44:13 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_len(t_env_list *ls)
{
	int	len;

	len = 0;
	while (ls)
	{
		len++;
		ls = ls->next;
	}
	return (len);
}

char	**env_to_arr(void)
{
	int			i;
	int			len;
	char		**env_arr;
	t_env_list	*ls;

	len = 0;
	i = 0;
	ls = data()->env_list;
	len = env_len(ls);
	env_arr = malloc(sizeof(char *) * (len + 1));
	env_arr[len] = NULL;
	while (i < len)
	{
		if (ls->value && *ls->value)
			env_arr[i] = ft_strjoin2(ft_strjoin2(ft_strjoin2(ls->name, "=\"", 0),
						ls->value, 1), "\"", 1);
		else
			env_arr[i] = ft_strdup(ls->name);
		ls = ls->next;
		i++;
	}
	return (env_arr);
}
