/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:55:45 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/03 19:58:01 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANALYSIS_H
# define ANALYSIS_H

# include "../pipex/libft/libft.h"

typedef enum
{
	TOK_IDENTIFIER,
	TOK_OPERATOR,
	TOK_LITERAL,
	TOK_REDIRECT,
	TOK_PIPE,
	TOK_END,
	TOK_INVALID
}				t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	char		*value;
	int			line;
	int			column;
}				t_token;

typedef struct s_tokenlist
{
	t_token		**token;
	int			set_count;
	int			*size;
}				t_tokenlist;

void			analysis(char *input);
void			lexical_analysis(t_tokenlist *tokenlist);

void			free_array(char **array);

#endif
