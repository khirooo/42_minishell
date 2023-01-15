/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:28:11 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/23 02:42:52 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*null_string(void)
{
	char	*str;

	str = malloc(1);
	if (!str)
		return (0);
	*str = 0;
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len, int flag)
{
	char			*substr;
	unsigned int	i;
	unsigned int	j;
	unsigned int	strlen;

	strlen = ft_strlen(s);
	if (strlen < (size_t)start)
		return (null_string());
	if (strlen < len)
		len = strlen - start;
	substr = (char *) malloc(len + 1);
	if (!s || !substr)
		return (NULL);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < len)
		substr[j++] = s[i++];
	substr[j] = 0;
	if (flag)
		free(s);
	return (substr);
}
