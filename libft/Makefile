# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edemirer <edemirer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 23:43:03 by edemirer          #+#    #+#              #
#    Updated: 2023/07/11 18:41:58 by edemirer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SOURCES = ft_atoi.c ft_isdigit.c ft_memmove.c ft_strlcat.c ft_strtrim.c ft_bzero.c ft_isprint.c ft_memset.c ft_strlcpy.c ft_strdup.c ft_calloc.c ft_split.c ft_strlen.c ft_tolower.c ft_itoa.c ft_isalnum.c ft_memchr.c ft_strchr.c ft_strncmp.c ft_toupper.c ft_isalpha.c ft_memcmp.c ft_strnstr.c ft_isascii.c ft_substr.c ft_memcpy.c ft_strjoin.c ft_strrchr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c ft_strmapi.c
OBJECTS = $(SOURCES:.c=.o)

BONUS_SOURCES = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)

$(NAME): $(OBJECTS)
	ar -rc $(NAME) $(OBJECTS)

all: $(NAME)

clean:
	rm -f $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(OBJECTS) $(BONUS_OBJECTS)
	ar -rc $(NAME) $(OBJECTS) $(BONUS_OBJECTS)

.PHONY: all bonus clean fclean re