# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 22:22:38 by yookamot          #+#    #+#              #
#    Updated: 2025/04/10 22:22:45 by yookamot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I./includes
# CFLAGS = -Wall -Wextra -Werror -I./includes  -fsanitize=address
LIBS = -lreadline

MANDATORY = minishell
BONUS = minishell_bonus

LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a

SRCS =  main.c \
		input.c\
		set_act.c\
		env_init.c\
		run_token.c\
		set_fd.c\
		set_fd_b.c\
		set_cmd.c\
		pipex.c\
		make_prosses.c\
		built_in_prosses.c\
		only_builtin.c\
		operators/get_full_path.c\
		operators/redirector.c\
		operators/here_document.c\
		operators/envp_list_to_char.c\
		error/error_1.c\
		error/error_2.c\
		error/error_3.c\
		error/error_4.c\
		error/error_5.c\
		error/error_6.c\
		utils/utils.c\
		get_next_line.c\
		get_next_line_utils.c\
		built_in_command/exit.c\
		built_in_command/cd.c\
		built_in_command/echo.c\
		built_in_command/env.c\
		built_in_command/export.c\
		built_in_command/pwd.c\
		built_in_command/sort_env.c\
		built_in_command/unset.c\
		analysis/lexer/analysis.c \
        analysis/lexer/get_quote_info.c \
        analysis/lexer/check_tokentype.c \
        analysis/lexer/ft_split_custom.c \
        analysis/lexer/get_tokens.c \
        analysis/lexer/get_tokentype.c \
        analysis/lexer/init_token.c \
        analysis/lexer/lexical_analysis.c \
        analysis/lexer/reshape_tokenlist.c \
		analysis/lexer/set_tokentype.c \
        analysis/lexer/split_token.c \
        analysis/lexer/free_tokenlist.c \
        analysis/lexer/utils.c \
		analysis/lexer/check_unclosed_quote.c \
		analysis/lexer/make_new_tokenset_with_quote.c \
        analysis/lexer/check_tokentype/check_single_symbol.c \
        analysis/lexer/check_tokentype/check_double_symbol.c \
        analysis/lexer/check_tokentype/check_env_var.c \
        analysis/lexer/check_tokentype/check_exit_status.c \
        analysis/lexer/check_tokentype/check_squote.c \
        analysis/lexer/check_tokentype/check_dquote.c \
        analysis/lexer/check_tokentype/check_redirection.c \

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