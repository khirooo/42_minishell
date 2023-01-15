/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:27:22 by kfergani          #+#    #+#             */
/*   Updated: 2022/05/17 19:27:09 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_flags
{
	int		hash;
	int		plus;
	int		space;
	int		zero;
	int		minus;
	int		width;
	int		prec;
}t_flags;

# define FT_BASE_LOWER  "0123456789abcdef"
# define FT_BASE_UPPER  "0123456789ABCDEF"

int		ft_printf(const char *format, ...);
void	reset_flags(t_flags *flags);
int		is_in(char c, const char *set);
int		ft_len_digit(int x);
int		ft_get_width(const char *format, int *i);
int		ft_get_prec(const char *format, int *i);
int		ft_printchar(char c, t_flags flags);
int		ft_printstr(char *s, t_flags flags);
int		ft_printnbr(int n, t_flags flags);
int		ft_printpercent(t_flags flags);
int		ft_printhex(unsigned int dec, char x, t_flags flags, char *null_byte);
int		ft_printunsigned(unsigned int n, t_flags flags);
int		ft_printptr(unsigned long long p, t_flags flags);
void	printstr(char *str, t_flags flags);
int		printnbr(char *nb, t_flags flags, int n, int len);
int		printunsigned(char *nb, t_flags flags, int len);
int		put_width(char c, int w);
int		to_zero(int c);
char	*ft_itoa_u(unsigned int n);
#endif