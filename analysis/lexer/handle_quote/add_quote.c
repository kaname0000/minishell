/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:54:29 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/12 21:29:53 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

static void	reshape_tokenset_with_quote(t_tokenset *tokenset, int i, int type,
		char *quote)
{
	t_token	**new;
	int		j;

	new = (t_token **)malloc(sizeof(t_token *) * (tokenset->count + 2));
	if (!new)
		free_tokenset(tokenset, FAILED);
	j = 0;
	while (j < i)
	{
		new[j] = tokenset->token[j];
		j++;
	}
	new[j] = (t_token *)malloc(sizeof(t_token));
	new[j]->value = ft_strdup(quote);
	new[j++]->type = type;
	new[j++] = tokenset->token[i];
	new[j] = (t_token *)malloc(sizeof(t_token));
	new[j]->value = ft_strdup(quote);
	new[j++]->type = type + 1;
	i++;
	while (i < tokenset->count)
		new[j++] = tokenset->token[i++];
	free(tokenset->token);
	tokenset->token = new;
	tokenset->count += 2;
}

// ── 2) add_quote の書き換え ──
//    「最初に見つかった１箇所だけ」を処理して抜ける
void	add_quote(t_tokenset *tokenset)
{
	int	i;

	i = 0;
	while (i < tokenset->count)
	{
		if (tokenset->token[i]->type == TOK_SQUOTE_IN && i > 0
			&& tokenset->token[i - 1]->type != TOK_SQUOTE_START)
		{
			reshape_tokenset_with_quote(tokenset, i, TOK_SQUOTE_START, "'");
			break ;
		}
		if (tokenset->token[i]->type == TOK_DQUOTE_IN && i > 0
			&& tokenset->token[i - 1]->type != TOK_DQUOTE_START)
		{
			reshape_tokenset_with_quote(tokenset, i, TOK_DQUOTE_START, "\"");
			break ;
		}
		i++;
	}
}
