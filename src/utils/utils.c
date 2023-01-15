/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 03:17:53 by kfergani          #+#    #+#             */
/*   Updated: 2022/10/30 20:21:36 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (*s1 && *s2 && (*s1 == *s2 || *s1 + 32 == *s2 || *s1 == *s2 + 32))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	handler(int signum)
{
	if (signum)
	{
		rl_free_line_state();
		rl_on_new_line();
		write (1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
