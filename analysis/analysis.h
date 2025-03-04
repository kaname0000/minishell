/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:55:45 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/04 19:19:55 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANALYSIS_H
# define ANALYSIS_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
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

void					free_array(void **array);
void					free_values(t_tokenlist *tokenlist, int i, int j);
void					malloc_failed(void);

#endif
