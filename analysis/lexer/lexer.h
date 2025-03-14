/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:55:45 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/14 14:19:07 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../analysis.h"
# include "../analysis_get_next_line/get_next_line.h"
# include "../analysis_libft/libft.h"
# include "check_tokentype/check_tokentype.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum					e_tokentype
{
	TOK_WORD,
	TOK_ASSIGNMENT,
	TOK_LITERAL,
	TOK_BUILTIN,
	TOK_PIPE,
	TOK_SEMICOLON,
	TOK_AMPERSAND,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_HEREDOC,
	TOK_SQUOTE_START,
	TOK_SQUOTE_IN,
	TOK_SQUOTE_END,
	TOK_DQUOTE_START,
	TOK_DQUOTE_IN,
	TOK_DQUOTE_END,
	TOK_BACKSLASH,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_ENV_VAR,
	TOK_ENV_VAR_NAME,
	TOK_EXIT_STATUS,
	TOK_NEWLINE,
	TOK_NULL,
	TOK_EOF,
	TOK_SPLIT
};

typedef struct s_token
{
	enum e_tokentype	type;
	char				*value;
	int					*squote;
	int					*dquote;
	int					count;
	struct s_token		**split_token;
}						t_token;

typedef struct s_tokenlist
{
	t_token				***token;
	int					set_count;
	int					*token_count;
}						t_tokenlist;

# define FAILED 0
# define SUCCESS 1

void					lexical_analysis(char *input, t_tokenlist *tokenlist);
void					get_tokens(char *input, t_tokenlist *tokenlist);
void					free_array(char **array);
void					free_tokenlist(t_tokenlist *tokenlist, char **array1,
							char **array2, int key);
void					check_tokentype(t_token *token, t_tokenlist *tokenlist);
char					**ft_split_custom(char *s, t_tokenlist *tokenlist,
							int i);
void					check_quote(t_tokenlist *tokenlist);
void					free_flag_array(t_tokenlist *tokenlist);
void					init_token(t_tokenlist *tokenlist);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strstr(const char *s1, const char *s2);
void					split_token(t_tokenlist *tokenlist, char *str,
							t_token *token, int count);
void					traverse_token_list(t_tokenlist *tokenlist);
void					remake_quote(t_tokenlist *tokenlist, t_token *token);
t_tokenlist				*analysis(char *input);
void					get_tokentype(t_token *token, t_token *pre_token);

void					print_token(t_tokenlist *tokenlist);

#endif
