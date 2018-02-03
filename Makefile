# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/07 09:26:14 by dvdovenk          #+#    #+#              #
#    Updated: 2017/04/26 18:31:54 by skavunen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = ft_ls.c \
		main.c \
		ft_display.c \
		ft_error.c \
		ft_filter.c \
		item.c \
		params.c \
		recursion.c \
		tools.c \
		view.c \
		ft_distoll.c

OBJ = $(SRC:.c=.o)

HEADER = ft_ls.h libft/libft.h

CC = gcc

LIBFTDIR = libft/

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME) : $(OBJ) $(LIBFTDIR)libft.a
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L./$(LIBFTDIR) -lft

$(LIBFTDIR)libft.a: libft/Makefile
	make -C libft/

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFTDIR) 

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFTDIR)libft.a

re: clean all
