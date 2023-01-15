/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:55:12 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/30 05:18:22 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin2(char *s1, char *s2, int flag)
{
	char			*dst;

	if (s1 == 0 || s2 == 0)
		return (0);
	dst = malloc(sizeof(*dst) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dst == 0)
	{
		if (flag)
			free(s1);
		return (0);
	}
	ft_memcpy(dst, s1, ft_strlen(s1));
	ft_memcpy(dst + ft_strlen(s1), s2, ft_strlen(s2));
	dst[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	if (flag)
		free(s1);
	return (dst);
}

char	*ft_strjoin_withnull(char *s1, char *s2, int flag)
{
	char			*dst;

	if (s2 == NULL)
		return (ft_strdup(s1));
	if (s1 == NULL)
		return (ft_strdup(s2));
	dst = malloc(sizeof(*dst) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dst == 0)
	{
		if (flag)
			free(s1);
		return (0);
	}
	ft_memcpy(dst, s1, ft_strlen(s1));
	ft_memcpy(dst + ft_strlen(s1), s2, ft_strlen(s2));
	dst[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	if (flag)
		free(s1);
	return (dst);
}
