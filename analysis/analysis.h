/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:55:45 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/10 14:19:50 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANALYSIS_H
# define ANALYSIS_H

# include "analysis_get_next_line/get_next_line.h"
# include "analysis_libft/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum					e_tokentype
{
	TOK_IDENTIFIER,
	TOK_OPERATOR,
	TOK_LITERAL,
	TOK_REDIRECT,
	TOK_PIPE,
	TOK_END,
	TOK_INVALID
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
	int					*size;
}						t_tokenlist;

# define FAILED 1
# define SUCCESS 0

t_tokenlist				*analysis(char *input);
void					lexical_analysis(t_tokenlist *tokenlist);

void					free_array(char **array);
void					free_token(t_tokenlist *tokenlist);
void					malloc_failed(void);
void					free_tokenlist(t_tokenlist *tokenlist);

#endif
