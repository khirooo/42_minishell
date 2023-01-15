/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:12:47 by kfergani          #+#    #+#             */
/*   Updated: 2022/10/30 03:00:45 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	printstr(char *str, t_flags flags)
{
	int		i;
	char	x;

	x = ' ';
	if (flags.zero != -1 && flags.minus == -1)
		x = '0';
	if (flags.minus == -1)
		put_width(x, flags.width);
	i = 0;
	while (i < flags.prec)
	{
		ft_putchar_fd(str[i], 2);
		i++;
	}
	if (flags.minus == 1)
		put_width(x, flags.width);
}

int	printnbr(char *nb, t_flags flags, int n, int len)
{
	char	c;

	c = ' ';
	if (flags.zero != -1 && flags.prec == -1 && flags.minus == -1)
		c = '0';
	if (c == ' ' && flags.minus == -1)
		put_width(c, flags.width);
	if (n < 0)
		ft_putchar_fd('-', 1);
	else if (flags.plus != -1)
		ft_putchar_fd('+', 1);
	else if (flags.space != -1)
		ft_putchar_fd(' ', 1);
	if (c == '0')
		put_width(c, flags.width);
	put_width('0', flags.prec);
	if (n < 0)
		ft_putstr_fd(nb + 1, 1);
	else if (len)
		ft_putstr_fd(nb, 1);
	if (flags.minus != -1)
		put_width(c, flags.width);
	if (n < 0 || ((flags.plus != -1 || flags.space != -1) && n >= 0))
		flags.width++;
	return (flags.width + to_zero(flags.prec) + len);
}

int	printunsigned(char *nb, t_flags flags, int len)
{
	char	c;

	c = ' ';
	if (flags.zero != -1 && flags.prec == -1 && flags.minus == -1)
		c = '0';
	if (c == ' ' && flags.minus == -1)
		put_width(c, flags.width);
	if (flags.plus != -1)
		ft_putchar_fd('+', 1);
	else if (flags.space != -1)
		ft_putchar_fd(' ', 1);
	if (c == '0')
		put_width(c, flags.width);
	put_width('0', flags.prec);
	if (len)
		ft_putstr_fd(nb, 1);
	if (flags.minus != -1)
		put_width(c, flags.width);
	if (flags.plus != -1 || flags.space != -1)
		flags.width++;
	return (flags.width + to_zero(flags.prec) + len);
}
