# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 18:55:13 by yookamot          #+#    #+#              #
#    Updated: 2025/04/29 22:04:33 by yookamot         ###   ########.fr        #
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
		operators/input.c\
		operators/set_act.c\
		env/env_init.c\
		operators/run_token.c\
		operators/set_fd.c\
		operators/set_fd_b.c\
		operators/set_cmd.c\
		operators/pipex.c\
		operators/make_prosses.c\
		operators/built_in_prosses.c\
		operators/only_builtin.c\
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
		free/free_array.c\
		free/free_cmd.c\
		free/free_list.c\
		free/free_mini.c\
		free/free_tokenset.c\
		built_in_command/exit.c\
		built_in_command/cd.c\
		built_in_command/echo.c\
		built_in_command/env.c\
		built_in_command/export.c\
		built_in_command/pwd.c\
		built_in_command/sort_env.c\
		built_in_command/unset.c\
		analysis/analysis.c \
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
		analysis/lexer/get_env.c \
		analysis/lexer/process_env_var.c \
        analysis/lexer/check_tokentype/check_single_symbol.c \
        analysis/lexer/check_tokentype/check_double_symbol.c \
        analysis/lexer/check_tokentype/check_squote.c \
        analysis/lexer/check_tokentype/check_dquote.c \
        analysis/lexer/check_tokentype/check_redirection.c \
		analysis/lexer/handle_quote/check_unclosed_quote.c \
		analysis/lexer/handle_quote/make_new_tokenset_with_quote.c \
		analysis/lexer/handle_quote/merge_quoted_tokens.c \
		analysis/lexer/handle_quote/make_quote_flag.c \
		analysis/lexer/handle_quote/get_quote_info.c \
		analysis/lexer/handle_quote/handle_quote.c \
		analysis/lexer/handle_quote/fix_command_token.c \
		analysis/lexer/handle_quote/reset_input.c \
		analysis/lexer/handle_quote/remove_quote_and_merge.c \
		analysis/lexer/handle_quote/delete_quote.c \
		analysis/lexer/handle_quote/make_new_value_in_quote.c \
		analysis/parser/check_pipe.c \
		analysis/parser/check_redirect.c \
		analysis/parser/parser_error.c \
		analysis/parser/syntax_analysis.c

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

run:all
	./$(MANDATORY)

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