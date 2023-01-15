# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 18:28:25 by kfergani          #+#    #+#              #
#    Updated: 2022/10/30 02:32:47 by kfergani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

LIBFT	=	../libft/
INCLUDE	=	./includes/
SRCDIR	=	./src/
OBJDIR	=	./objs

SOURCES	=	ft_printf.c ft_printf_utils.c ft_print_conv.c print_conv.c hex_stuff.c ft_itoa_u.c\


SRCS	=	$(addprefix $(SRCDIR)/, $(SOURCES))
OBJS	=	$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))



all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@cp ../libft/libft.a $(NAME)
	@ar rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDE)/ft_printf.h
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) -I $(INCLUDE) -o $@ -c $<

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJDIR)
	make clean -C $(LIBFT)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
