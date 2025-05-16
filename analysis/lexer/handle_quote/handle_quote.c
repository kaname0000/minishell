/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:01:08 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/12 21:41:23 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	handle_quote(t_tokenset *tokenset)
{
	while (check_unclosed_quote(tokenset))
		set_tokentype(tokenset);
	while (merge_quoted_tokens(tokenset))
		;
	while (fix_command_token(tokenset))
		set_tokentype(tokenset);
	while (delete_quotes(tokenset))
		;
}
