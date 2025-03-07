/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:55:45 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/07 15:18:47 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../analysis_get_next_line/get_next_line.h"
# include "../analysis_libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum					e_tokentype
{
	TOK_WORD,
	TOK_ASSIGNMENT,
	TOK_BUILTIN,
	TOK_PIPE,
	TOK_SEMICOLON,
	TOK_AMPERSAND,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_HEREDOC,
	TOK_SQUOTE,
	TOK_DQUOTE,
	TOK_BACKSLASH,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_ENV_VAR,
	TOK_EXIT_STATUS,
	TOK_NEWLINE,
	TOK_EOF
};

typedef struct s_token
{
	enum e_tokentype	type;
	char				*value;
	int					line;
	int					column;
}						t_token;

typedef struct s_tokenlist
{
	t_token				**token;
	int					set_count;
	int					*token_count;
}						t_tokenlist;

# define FAILED 1
# define SUCCESS 0

void					lexical_analysis(char *input, t_tokenlist *tokenlist);
void					get_tokens(char *input, t_tokenlist *tokenlist);
void					free_array(char **array);
void					free_token(t_tokenlist *tokenlist);
void					malloc_failed(void);
void					free_tokenlist(t_tokenlist *tokenlist);
void					check_token(t_token *token);
char					**ft_split_custom(char const *s, char c);
void					check_quote(t_tokenlist *tokenlist);

t_tokenlist				*analysis(char *input);

#endif
