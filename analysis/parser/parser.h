/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:37:21 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/16 17:23:49 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../analysis.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	check_pipe(t_tokenset *tokenset, int i);
int	check_redirect(t_tokenset *tokenset, int i);
int	parser_error(t_tokenset *tokenset, char *value);
int	syntax_analysis(t_tokenset *tokenset);

#endif