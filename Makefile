# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okaname <okaname@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 14:19:36 by okaname           #+#    #+#              #
#    Updated: 2025/03/24 20:51:19 by okaname          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

hCC = cc
# CFLAGS = -Wall -Wextra -Werror -I./includes -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -I./includes 
LIBS = -lreadline

MANDATORY = minishell
BONUS = minishell_bonus

LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a

SRCS =  main.c \
		input.c\
		set_act.c\
		env_init.c\
		operators/get_full_path.c\
		operators/redirector.c\
		operators/here_document.c\
		operators/openfile.c\
		error/error_1.c\
		error/error_2.c\
		error/error_3.c\
		error/error_4.c\
		error/error_5.c\
		utils/utils.c\
		built_in_command/exit.c\
		built_in_command/cd.c\
		built_in_command/echo.c\
		built_in_command/env.c\
		built_in_command/export.c\
		built_in_command/pwd.c\
		built_in_command/sort_env.c\
		built_in_command/unset.c\

OBJS = $(SRCS:.c=.o)

all: $(MANDATORY)

$(MANDATORY): $(LIBFT) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $@

$(BONUS): $(LIBFT) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $@


$(LIBFT):
	make -C $(LIBFTDIR) bonus

bonus: $(BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) 
	make -C $(LIBFTDIR) clean
# 	make -C $(PIPEXDIR) clean

fclean: clean
	rm -f $(MANDATORY) $(BONUS)
	make -C $(LIBFTDIR) fclean
#	make -C $(PIPEXDIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re