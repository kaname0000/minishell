/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:53:55 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/08 20:08:03 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../built_in_command/built_in.h"
# include "../../free/free.h"
# include "../../libft/libft.h"
# include "../../struct.h"
# include "../analysis.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define FRONT 1   //クオートとその前をくっつける場合（hello" world）
# define BACK 2    //クオートとその後をくっつける場合（hello "world）
# define BOTH 3    //クオートとその前後をくっつける場合（hello"world）
# define NO_JOIN 0 //何もくっつけない場合（hello " world）

t_tokenset	*lexical_analysis(t_tokenlist *tokenlist, t_mini *mini);
void		get_tokens(t_tokenlist *tokenlist);
// void		free_array(char **array);
void		free_tokenlist(t_tokenlist *tokenlist, char **array1, char **array2,
				int key);
void		check_tokentype(t_token *token, t_tokenlist *tokenlist);
char		**ft_split_custom(char *s, t_tokenlist *tokenlist, int i);
void		init_token(t_token *token, char *str, t_tokenlist *tokenlist);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strstr(const char *s1, const char *s2);
void		split_token(t_tokenlist *tokenlist, char *str, t_token *token,
				int count);
void		get_tokentype(t_token *token, t_token *pre_token);
t_tokenset	*reshape_tokenlist(t_tokenlist *tokenlist);
void		free_tokenset(t_tokenset *tokenset, int key);
void		set_tokentype(t_tokenset *tokenset);
void		get_quote_info(t_token *token, t_token *pre);
int			merge_quoted_tokens(t_tokenset *tokenset);
int			check_unclosed_quote(t_tokenset *tokenset);
int			make_new_tokenset_with_quote(t_tokenset *tokenset, int i, int j);
char		*get_env(t_mini *mini, char *env, t_tokenlist *tokenlist);
void		process_env_var(t_tokenlist *tokenlist, t_mini *mini);
int			make_quote_flag(t_tokenlist *tokenlist);
void		malloc_failed(void);
int			check_single_symbol(t_token *token, int c, t_tokenlist *tokenlist);
int			check_double_symbol(t_token *token, char *symbol,
				t_tokenlist *tokenlist);
int			check_squote(t_token *token, t_tokenlist *tokenlist);
int			check_dquote(t_token *token, t_tokenlist *tokenlist);
int			check_redirection_in(t_token *token, t_tokenlist *tokenlist);
int			check_redirection_out(t_token *token, t_tokenlist *tokenlist);
int			count_quote_in_input(t_tokenset *tokenset, int i, char *quote);
int			check_input(char *input, int count, char *value);
int			fix_command_token(t_tokenset *tokenset);
void		handle_quote(t_tokenset *tokenset);
void		reset_input(t_tokenset *tokenset, int i, int j, int key);
void		remove_token(t_tokenset *tokenset, int i, int minus);
void		remove_quote_and_merge_ex(t_tokenset *tokenset, int i);
int			delete_quotes(t_tokenset *tokenset);
int			search_quote(t_tokenset *tokenset, int x);
char		*make_new_empty_value(t_tokenset *tokenset, int i);
char		*make_new_value(char *input, int a, int b);
void		search_daller(t_tokenset *tokenset);

#endif
