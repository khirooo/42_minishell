/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:31:11 by kfergani          #+#    #+#             */
/*   Updated: 2022/05/15 21:56:44 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	reset_flags(t_flags *flags)
{
	flags->hash = -1;
	flags->minus = -1;
	flags->plus = -1;
	flags->prec = -1;
	flags->space = -1;
	flags->width = -1;
	flags->zero = -1;
}

int	is_in(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

int	ft_len_digit(int x)
{
	int		len;
	char	*num;

	num = ft_itoa(x);
	if (!num)
		return (0);
	len = (int)ft_strlen(num);
	free(num);
	return (len);
}

int	ft_get_width(const char *format, int *i)
{
	int		x;

	x = ft_atoi(&format[*i]);
	*i = *i + ft_len_digit(x) - 1;
	return (x);
}

int	ft_get_prec(const char *format, int *i)
{
	int	x;
	int	nb_zeros;

	nb_zeros = 0;
	x = *i;
	while (format[x++] == '0')
		nb_zeros++;
	x = ft_atoi(format + *i);
	if (x == 0)
		*i = *i + nb_zeros;
	else
		*i = *i + ft_len_digit(x) + nb_zeros;
	return (x);
}
