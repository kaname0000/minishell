/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:37:21 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/10 17:37:31 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../analysis.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum				e_nodetype
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT
};

typedef struct s_ast
{
	e_nodetype		type;
	char			**argv;
	char			*filename;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

#endif
