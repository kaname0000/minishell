/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_quote_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:15:40 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/29 20:59:56 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

// quoteのフラグ配列作成
void	make_quote_flag(t_tokenlist *tokenlist)
{
	size_t	i;
	size_t	len;
	int		in_s;
	int		in_d;

	len = ft_strlen(tokenlist->input);
	in_s = 0;
	in_d = 0;
	i = 0;
	while (i < len)
	{
		if (tokenlist->input[i] == '\'' && !in_d)
			in_s = !in_s;
		else if (tokenlist->input[i] == '"' && !in_s)
			in_d = !in_d;
		tokenlist->sflag[i] = in_s;
		tokenlist->dflag[i] = in_d;
		i++;
	}
	if (in_s)
		ft_bzero(tokenlist->sflag, len * sizeof(int));
	if (in_d)
		ft_bzero(tokenlist->dflag, len * sizeof(int));
}
