/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:25:05 by kfergani          #+#    #+#             */
/*   Updated: 2022/10/30 03:02:01 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	put_width(char c, int w)
{
	int	i;

	i = 0;
	while (i < w)
	{
		ft_putchar_fd(c, 2);
		i++;
	}
	return (i);
}

int	to_zero(int c)
{
	if (c < 0)
		return (0);
	return (c);
}

static t_flags	ft_handel_flags(const char *format, int *i)
{
	t_flags	flags;

	reset_flags(&flags);
	while (!is_in(format[*i], "dcsiupxX%"))
	{
		if (format[*i] == '#')
			flags.hash = 1;
		else if (format[*i] == ' ')
			flags.space = 1;
		else if (format[*i] == '+')
			flags.plus = 1;
		else if (format[*i] == '-')
			flags.minus = 1;
		else if (format[*i] == '0')
			flags.zero = 1;
		else if (ft_isdigit(format[*i]))
			flags.width = ft_get_width(format, i);
		else if (format[*i] == '.')
			flags.prec = ft_get_prec(format + 1, i);
		(*i)++;
	}
	return (flags);
}

static int	ft_print_format(const char *format, int i, t_flags flag, va_list ag)
{
	int	len;

	len = 0;
	if (format[i] == 'c')
		len = ft_printchar(va_arg(ag, int), flag);
	else if (format[i] == 's')
		len = ft_printstr(va_arg(ag, char *), flag);
	else if (format[i] == 'p')
		len = ft_printptr(va_arg(ag, unsigned long long), flag);
	else if (format[i] == 'd' || format[i] == 'i')
		len = ft_printnbr(va_arg(ag, int), flag);
	else if (format[i] == 'u')
		len = ft_printunsigned(va_arg(ag, unsigned int), flag);
	else if (format[i] == 'x')
		len = ft_printhex(va_arg(ag, unsigned int), format[i], flag, "0x");
	else if (format[i] == 'X')
		len = ft_printhex(va_arg(ag, unsigned int), format[i], flag, "0X");
	else if (format[i] == '%')
		len = ft_printpercent(flag);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	t_flags	flags;
	va_list	args;
	int		len;
	int		i;

	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			flags = ft_handel_flags(format, &i);
			len += ft_print_format(format, i, flags, args);
		}
		else
		{
			ft_putchar_fd(format[i], 2);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}
