/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 01:10:38 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/16 17:25:05 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../built_in_command/built_in.h"
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
	TOK_BUILTIN,
	TOK_PIPE,
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
	TOK_ENV_VAR,
	TOK_ENV_VAR_NAME,
	TOK_EXIT_STATUS,
	TOK_NEWLINE,
	TOK_NULL,
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
	int					is_complete;
}						t_token;

typedef struct s_tokenlist
{
	t_token				***token;
	char				*input;
	int					set_count;
	int					*token_count;
	int					*sflag;
	int					*dflag;
}						t_tokenlist;

typedef struct s_tokenset
{
	t_token				**token;
	int					count;
	char				*input;
}						t_tokenset;

# define FAILED 0
# define SUCCESS 1

t_tokenset				*lexical_analysis(t_tokenlist *tokenlist, t_mini *mini);
void					get_tokens(t_tokenlist *tokenlist);
void					free_array(char **array);
void					free_tokenlist(t_tokenlist *tokenlist, char **array1,
							char **array2, int key);
void					check_tokentype(t_token *token, t_tokenlist *tokenlist,
							t_mini *mini);
char					**ft_split_custom(char *s, t_tokenlist *tokenlist,
							int i);
void					init_token(t_token *token, char *str,
							t_tokenlist *tokenlist);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strstr(const char *s1, const char *s2);
void					split_token(t_tokenlist *tokenlist, char *str,
							t_token *token, int count);
void					get_tokentype(t_token *token, t_token *pre_token);
t_tokenset				*reshape_tokenlist(t_tokenlist *tokenlist);
void					free_tokenset(t_tokenset *tokenset, int key);
void					set_tokentype(t_tokenset *tokenset);
void					get_quote_info(t_token *token, t_token *pre);
void					process_quoted_tokens(t_tokenset *tokenset);
int						check_unclosed_quote(t_tokenset *tokenset);
int						make_new_tokenset_with_quote(t_tokenset *tokenset,
							int i, int j);
char					*get_env(t_mini *mini, char *env,
							t_tokenlist *tokenlist);
void					process_env_var(t_tokenlist *tokenlist, t_mini *mini);

#endif
