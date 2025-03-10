/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokentype.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamotoyota <okamotoyota@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:48:15 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/11 03:28:24 by okamotoyota      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_TOKENTYPE_H
# define CHECK_TOKENTYPE_H

# include "../lexer.h"

int	check_env_var(t_token *token, t_tokenlist *tokenlist);
int	check_exit_status(t_token *token);
int	check_squote(t_token *token);
int	check_dquote(t_token *token);

#endif