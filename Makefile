# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okaname <okaname@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 14:19:36 by okaname           #+#    #+#              #
#    Updated: 2025/03/03 15:38:44 by okaname          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

hCC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -lreadline

MANDATORY = minishell
BONUS = minishell_bonus

LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a
PIPEXDIR = ./pipex
PIPEX = $(PIPEXDIR)/pipex.a

SRCS =  main.c \
		input.c

OBJS = $(SRCS:.c=.o)

all: $(MANDATORY)

$(MANDATORY): $(LIBFT) $(PIPEX) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PIPEX) -o $@

$(BONUS): $(LIBFT) $(PIPEX) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PIPEX) -o $@


$(LIBFT):
	make -C $(LIBFTDIR) bonus

$(PIPEX):
	make -C $(PIPEXDIR)

bonus: $(BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) 
	make -C $(LIBFTDIR) clean
	make -C $(PIPEXDIR) clean

fclean: clean
	rm -f $(MANDATORY) $(BONUS)
	make -C $(LIBFTDIR) fclean
	make -C $(PIPEXDIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re