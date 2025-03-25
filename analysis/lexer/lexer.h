/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2025/03/26 00:34:42 by okaname           #+#    #+#             */
/*   Updated: 2025/03/26 00:52:14 by okaname          ###   ########.fr       */
=======
/*   Created: 2025/03/03 15:55:45 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/26 00:29:44 by yookamot         ###   ########.fr       */
>>>>>>> d79cecb (muzuine)
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../get_next_line.h"
# include "../../libft/libft.h"
# include "../analysis.h"
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
	TOK_SPLIT,
	UNSIGNED
};

typedef struct s_token
{
	enum e_tokentype	type;
	char				*value;
	int					squote;
	int					dquote;
	int					count;
	struct s_token		**split_token;
}						t_token;

typedef struct s_tokenlist
{
	t_token				***token;
	int					set_count;
	int					*token_count;
}						t_tokenlist;

typedef struct s_tokenset
{
	t_token				**token;
	int					count;
}						t_tokenset;

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
void					init_token(t_tokenlist *tokenlist);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strstr(const char *s1, const char *s2);
void					split_token(t_tokenlist *tokenlist, char *str,
							t_token *token, int count);
void					traverse_token_list(t_tokenlist *tokenlist);
t_tokenlist				*analysis(char *input);
void					get_tokentype(t_token *token, t_token *pre_token);
void					set_quote_info(t_token *token, t_token *pre_token,
							t_token *pre_pre_token);
t_tokenset				*reshape_tokenlist(char *input, t_tokenlist *tokenlist);
void					tokenize_with_quotes(char *input, t_tokenset *tokenset);

#endif
