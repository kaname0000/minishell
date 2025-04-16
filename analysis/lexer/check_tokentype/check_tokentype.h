/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokentype.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:48:15 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/16 19:20:27 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_TOKENTYPE_H
# define CHECK_TOKENTYPE_H

# include "../lexer.h"

struct s_token;
struct s_tokenlist;
typedef struct s_token		t_token;
typedef struct s_tokenlist	t_tokenlist;

int							check_single_symbol(t_token *token, int c,
								t_tokenlist *tokenlist);
int							check_double_symbol(t_token *token, char *symbol,
								t_tokenlist *tokenlist);
int							check_squote(t_token *token,
								t_tokenlist *tokenlist);
int							check_dquote(t_token *token,
								t_tokenlist *tokenlist);
int							check_redirection_in(t_token *token,
								t_tokenlist *tokenlist);
int							check_redirection_out(t_token *token,
								t_tokenlist *tokenlist);

#endif