NAME = analysis

# コンパイラ設定
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I. -I./lexer -I./analysis_get_next_line -I./lexer/check_tokentype

# ソースディレクトリ
SRC_DIR_LEXER = ./lexer
SRC_DIR_GNL = ./analysis_get_next_line

# ソースファイル
SRCS_LEXER = $(SRC_DIR_LEXER)/analysis.c \
             $(SRC_DIR_LEXER)/check_tokentype.c \
             $(SRC_DIR_LEXER)/ft_split_custom.c \
             $(SRC_DIR_LEXER)/get_tokens.c \
             $(SRC_DIR_LEXER)/get_tokentype.c \
             $(SRC_DIR_LEXER)/init_token.c \
             $(SRC_DIR_LEXER)/lexical_analysis.c \
             $(SRC_DIR_LEXER)/set_quote_info.c \
             $(SRC_DIR_LEXER)/split_token.c \
             $(SRC_DIR_LEXER)/test_main.c \
             $(SRC_DIR_LEXER)/traverse_tokens.c \
             $(SRC_DIR_LEXER)/free_tokenlist.c \
             $(SRC_DIR_LEXER)/utils.c \
             $(SRC_DIR_LEXER)/check_tokentype/check_single_symbol.c \
             $(SRC_DIR_LEXER)/check_tokentype/check_double_symbol.c \
             $(SRC_DIR_LEXER)/check_tokentype/check_env_var.c \
             $(SRC_DIR_LEXER)/check_tokentype/check_exit_status.c \
             $(SRC_DIR_LEXER)/check_tokentype/check_squote.c \
             $(SRC_DIR_LEXER)/check_tokentype/check_dquote.c \
             $(SRC_DIR_LEXER)/check_tokentype/check_backslash.c \
             $(SRC_DIR_LEXER)/check_tokentype/check_redirection.c \
             $(SRC_DIR_LEXER)/check_tokentype/check_assignment.c

SRCS_GNL = $(SRC_DIR_GNL)/get_next_line.c \
           $(SRC_DIR_GNL)/get_next_line_utils.c

# オブジェクトファイル
OBJS_LEXER = $(SRCS_LEXER:.c=.o)
OBJS_GNL = $(SRCS_GNL:.c=.o)

# コンパイルターゲット
all: $(NAME)

$(NAME): $(OBJS_LEXER) $(OBJS_GNL) libft
	$(CC) $(CFLAGS) $(OBJS_LEXER) $(OBJS_GNL) -L./analysis_libft -lft -o $(NAME)

$(SRC_DIR_LEXER)/%.o: $(SRC_DIR_LEXER)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR_GNL)/%.o: $(SRC_DIR_GNL)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# libftのコンパイルを呼び出し
libft:
	$(MAKE) -C ./analysis_libft

# クリーンアップ
clean:
	rm -f $(OBJS_LEXER) $(OBJS_GNL)
	$(MAKE) -C ./analysis_libft clean

# 完全なクリーンアップ（実行ファイルを削除）
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./analysis_libft fclean

# 再ビルド
re: fclean all

.PHONY: all clean fclean re
