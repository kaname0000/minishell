/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:55:45 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/09 22:02:09 by yookamot         ###   ########.fr       */
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
	TOK_BUILTIN, // clear
	TOK_PIPE,    // clear
	TOK_SEMICOLON,
	TOK_AMPERSAND,    // clear
	TOK_REDIR_IN,     // clear
	TOK_REDIR_OUT,    // clear
	TOK_REDIR_APPEND, // clear
	TOK_HEREDOC,      // clear
	TOK_SQUOTE,
	TOK_DQUOTE,
	TOK_BACKSLASH, // clear
	TOK_LPAREN,    // clear
	TOK_RPAREN,    // clear
	TOK_ENV_VAR,
	TOK_EXIT_STATUS, // clear
	TOK_NEWLINE,     // clear
	TOK_EOF          // clear
};

typedef struct s_token
{
	enum e_tokentype	type;
	char				*value;
}						t_token;

typedef struct s_tokenlist
{
	t_token				***token;
	int					set_count;
	int					*token_count;
}						t_tokenlist;

# define FAILED 1
# define SUCCESS 0

void					lexical_analysis(char *input, t_tokenlist *tokenlist);
void					get_tokens(char *input, t_tokenlist *tokenlist);
void					free_array(char **array);
void					free_tokenlist(t_tokenlist *tokenlist, char **array1,
							char **array2, int key);
void					check_token(t_token *token);
char					**ft_split_custom(char const *s, t_tokenlist *tokenlist,
							int i);
void					check_single_and_double_quote(char **array);
t_tokenlist				*analysis(char *input);

#endif
