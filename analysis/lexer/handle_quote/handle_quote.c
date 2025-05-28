/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:01:08 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/28 17:45:15 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	handle_quote(t_tokenset *tokenset)
{
	insert_space_between_symbol_and_quote(tokenset);
	while (check_unclosed_quote(tokenset))
		set_tokentype(tokenset);
	while (merge_quoted_tokens(tokenset))
		;
	while (fix_command_token(tokenset))
		set_tokentype(tokenset);
	while (delete_quotes(tokenset))
		;
}
