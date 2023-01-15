# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/12 12:38:50 by rkedida           #+#    #+#              #
#    Updated: 2022/10/30 20:25:59 by rkedida          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

SOURCES 	= $(shell find ./src -name "*.c")
HEADERS 	= $(shell find ./includes -name "*.h")

LIBFT		= ./ft_printf/libftprintf.a

OBJECTS 	= $(patsubst %.c, %.o, $(SOURCES))

CC		= gcc
CFLAGS 		= -Wall -Wextra -Werror -g
RLFLAGS 	= -lreadline

all: $(NAME)

%.o: %.c
	@$(CC) -Iincludes $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@make -C ./ft_printf --silent
	@echo "Dependencies Compiled !"
	@$(CC) $(CFLAGS) $(RLFLAGS) $(LIBFT) -Iincludes $(OBJECTS) -o $(NAME)
	@echo "Compiled !"

clean:
	@make fclean -C ./ft_printf --silent
	-@$(RM) $(OBJECTS) $(DEPENDS)
	-@$(RM) $(OBJECTS)
	@echo "Everything is Cleaned !"

fclean: clean
	-@$(RM) $(NAME)

test:
	@$(shell ./esh_tester.sh)

git:
	@git add .
	-@git commit -m "Update!"
	@git push
	@echo "Commited!"

run: all
	./$(NAME)

re: clean all

.PHONY: re run fclean clean all
