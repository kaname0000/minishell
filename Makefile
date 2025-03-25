# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okaname <okaname@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 23:15:25 by okaname           #+#    #+#              #
#    Updated: 2025/03/25 23:16:04 by okaname          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
# CFLAGS = -Wall -Wextra -Werror -I./includes -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -I./includes 
LIBS = -lreadline -L./libft -lft

MANDATORY = minishell
BONUS = minishell_bonus

ANALYSISDIR = ./analysis
ANALYSIS = $(ANALYSISDIR)/analysis.a

SRCS =  main.c \
		input.c\
		set_act.c\
		openfile.c\
		env_init.c\
		operators/get_full_path.c\
		operators/redirector.c\
		operators/here_document.c\
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

$(MANDATORY): $(ANALYSIS) $(OBJS) 
	$(CC) $(CFLAGS) $(ANALYSIS) $(OBJS) $(LIBS) -o $@

$(BONUS): $(ANALYSIS) $(OBJS) 
	$(CC) $(CFLAGS) $(ANALYSIS) $(OBJS) $(LIBS) -o $@

$(ANALYSIS):
	make -C $(ANALYSISDIR) 

bonus: $(BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) 
	make -C $(ANALYSISDIR) clean

fclean: clean
	rm -f $(MANDATORY) $(BONUS)
	make -C $(ANALYSISDIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
