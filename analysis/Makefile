NAME = analysis
LIB_NAME = analysis.a

# コンパイラ設定
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I./lexer -I../get_next_line -I./lexer/check_tokentype

# ソースディレクトリ
SRC_DIR_LEXER = ./lexer
SRC_DIR_GNL = ../get_next_line

LIBFTDIR = ../libft
LIBFT = $(LIBFTDIR)/libft.a

# ソースファイル
SRCS_LEXER = $(SRC_DIR_LEXER)/analysis.c \
             $(SRC_DIR_LEXER)/check_quote.c \
             $(SRC_DIR_LEXER)/check_tokentype.c \
             $(SRC_DIR_LEXER)/ft_split_custom.c \
             $(SRC_DIR_LEXER)/get_tokens.c \
             $(SRC_DIR_LEXER)/get_tokentype.c \
             $(SRC_DIR_LEXER)/init_token.c \
             $(SRC_DIR_LEXER)/lexical_analysis.c \
             $(SRC_DIR_LEXER)/split_token.c \
             $(SRC_DIR_LEXER)/split_token_quote.c \
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
all: $(LIB_NAME)

$(LIB_NAME): $(OBJS_LEXER) $(OBJS_GNL) $(LIBFT)
	ar rcs $@ $^

# 個別のオブジェクトファイルの作成
$(SRC_DIR_LEXER)/%.o: $(SRC_DIR_LEXER)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR_GNL)/%.o: $(SRC_DIR_GNL)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# libftのコンパイルを呼び出し
$(LIBFT):
	$(MAKE) -C ../libft bonus

# クリーンアップ
clean:
	rm -f $(OBJS_LEXER) $(OBJS_GNL)
	$(MAKE) -C ../libft clean

# 完全なクリーンアップ（実行ファイルを削除）
fclean: clean
	rm -f $(LIB_NAME)
	$(MAKE) -C ../libft fclean

# 再ビルド
re: fclean all

.PHONY: all clean fclean re
