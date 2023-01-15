/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_conv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:42:26 by kfergani          #+#    #+#             */
/*   Updated: 2022/05/17 19:07:15 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printchar(char c, t_flags flags)
{
	if (flags.minus != -1)
		ft_putchar_fd(c, 1);
	put_width(' ', flags.width - 1);
	if (flags.minus == -1)
		ft_putchar_fd(c, 1);
	flags.width--;
	return (to_zero(flags.width) + 1);
}

int	ft_printstr(char *s, t_flags flags)
{
	if (!s)
	{
		s = ft_strdup("(null)");
		if (flags.prec == -1 || flags.prec > (int)ft_strlen(s))
			flags.prec = ft_strlen(s);
		flags.width = flags.width - flags.prec;
		if (flags.width < 0)
			flags.width = 0;
		printstr(s, flags);
		free(s);
	}
	else
	{
		if (flags.prec == -1 || flags.prec > (int)ft_strlen(s))
			flags.prec = ft_strlen(s);
		flags.width = flags.width - flags.prec;
		if (flags.width < 0)
			flags.width = 0;
		printstr(s, flags);
	}
	return (flags.width + flags.prec);
}

int	ft_printnbr(int n, t_flags flags)
{
	char	*nb;
	int		len;

	nb = ft_itoa(n);
	len = ft_strlen(nb);
	if (n < 0 || (n == 0 && flags.prec == 0))
		len--;
	if (flags.prec > len)
	{
		flags.prec -= len;
		flags.width = flags.width - flags.prec - len;
	}
	else
	{
		flags.width -= len;
		if (flags.prec != -1)
			flags.prec = 0;
	}
	if (n < 0 || ((flags.plus != -1 || flags.space != -1) && n >= 0))
		flags.width--;
	if (flags.width < 0)
		flags.width = 0;
	len = printnbr(nb, flags, n, len);
	free(nb);
	return (len);
}

int	ft_printpercent(t_flags flags)
{
	int		c;

	c = ' ';
	if (flags.zero != -1)
		c = '0';
	if (flags.minus == -1)
		put_width(c, flags.width - 1);
	ft_putchar_fd('%', 1);
	if (flags.minus != -1)
		put_width(' ', flags.width - 1);
	flags.width--;
	return (to_zero(flags.width) + 1);
}

int	ft_printunsigned(unsigned int n, t_flags flags)
{
	char	*nb;
	int		len;

	nb = ft_itoa_u(n);
	len = ft_strlen(nb);
	if (n == 0 && flags.prec == 0)
		len--;
	if (flags.prec > len)
	{
		flags.prec -= len;
		flags.width = flags.width - flags.prec - len;
	}
	else
	{
		flags.width -= len;
		if (flags.prec != -1)
			flags.prec = 0;
	}
	if (flags.plus != -1 || flags.space != -1)
		flags.width--;
	if (flags.width < 0)
		flags.width = 0;
	len = printunsigned(nb, flags, len);
	free(nb);
	return (len);
}
