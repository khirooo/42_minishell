/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:09:08 by kfergani          #+#    #+#             */
/*   Updated: 2022/05/16 21:08:45 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_len_hex(unsigned long long x, int prev, int *bytes)
{
	if (x < 16 && prev == 1)
		(*bytes)++;
	if (x >= 16)
	{
		ft_len_hex(x / 16, 0, bytes);
		ft_len_hex(x % 16, 0, bytes);
	}
	else
		(*bytes)++;
}

static	char	*ft_ptohex(unsigned long long n, char x)
{
	char			*str;
	int				len;

	len = 0;
	ft_len_hex(n, (n >= 16), &len);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		if (x == 'x')
			str[len--] = FT_BASE_LOWER[(n % 16)];
		else
			str[len--] = FT_BASE_UPPER[(n % 16)];
		n /= 16;
	}
	return (str);
}

void	printhex(char *hex, t_flags flags, int len, char *null_byte)
{
	int		i;
	char	x;

	x = ' ';
	i = 0;
	if (flags.zero != -1 && flags.minus == -1 && flags.prec == -1)
		x = '0';
	if (flags.hash != -1 && !(!ft_strncmp(hex, "0", 1) && ft_strlen(hex) == 1)
		&& x == '0')
		ft_putstr_fd(null_byte, 1);
	if (flags.minus == -1)
		put_width(x, flags.width);
	if (flags.hash != -1 && !(!ft_strncmp(hex, "0", 1) && ft_strlen(hex) == 1)
		&& x == ' ')
		ft_putstr_fd(null_byte, 1);
	i = 0;
	while (i++ < flags.prec)
		ft_putchar_fd('0', 1);
	if (len)
		ft_putstr_fd(hex, 1);
	i = 0;
	if (flags.minus == 1)
		put_width(x, flags.width);
	free(hex);
}

int	ft_printhex(unsigned int dec, char x, t_flags flags, char *null_byte)
{
	char	*hex;
	int		len;

	hex = ft_ptohex(dec, x);
	len = ft_strlen(hex);
	if (dec == 0 && flags.prec == 0)
		len--;
	if (flags.prec != -1)
		flags.prec = to_zero(flags.prec - len);
	if (dec != 0 && flags.hash != -1)
		flags.width -= 2;
	if (flags.prec != -1)
		flags.width = to_zero(flags.width - flags.prec - len);
	else
		flags.width = to_zero(flags.width - len);
	printhex(hex, flags, len, null_byte);
	if (flags.prec == -1)
		flags.prec = 0;
	if (dec != 0 && flags.hash != -1)
		flags.width += 2;
	return (flags.width + flags.prec + len);
}

int	ft_printptr(unsigned long long p, t_flags flags)
{
	char	*hex;
	int		len;
	char	x;

	x = ' ';
	if (flags.zero != -1 && flags.minus == -1 && flags.prec == -1)
		x = '0';
	hex = ft_ptohex(p, 'x');
	len = ft_strlen(hex);
	if (!p && flags.prec == 0)
		len--;
	flags.width = to_zero(flags.width - to_zero(flags.prec - len) - len - 2);
	if (flags.minus == -1 && x != '0')
		put_width(x, flags.width);
	ft_putstr_fd("0x", 1);
	if (flags.minus == -1 && x == '0')
		put_width(x, flags.width);
	put_width('0', flags.prec - len);
	if (len)
		ft_putstr_fd(hex, 1);
	if (flags.minus != -1)
		put_width(x, flags.width);
	free(hex);
	return (flags.width + to_zero(flags.prec - len) + len + 2);
}
