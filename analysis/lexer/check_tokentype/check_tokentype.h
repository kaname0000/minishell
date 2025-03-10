/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokentype.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:48:15 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/10 19:49:22 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_TOKENTYPE_H
# define CHECK_TOKENTYPE_H

# include "../lexer.h"

int	check_env_var(t_token *token);
int	check_exit_status(t_token *token);

#endif