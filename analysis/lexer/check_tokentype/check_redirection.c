/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:48:33 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/29 20:58:02 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_tokentype.h"

static int	count_redirection_in(t_token *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token->value[i])
	{
		if (token->value[i] == '<' && !(i && token->value[i - 1] == '<')
			&& token->value[i + 1] != '<')
		{
			count++;
			if (token->squote || token->dquote || (i != 0 && token->value[i
					- 1] == '\\'))
				break ;
			else
				return (count);
		}
		i++;
	}
	return (FAILED);
}

int	check_redirection_in(t_token *token, t_tokenlist *tokenlist)
{
	int		count;
	char	*symbol;

	count = count_redirection_in(token);
	if (!count)
		return (FAILED);
	symbol = ft_strdup("<");
	if (!symbol)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	split_token(tokenlist, symbol, token, count);
	if (token->type != TOK_SPLIT)
		return (FAILED);
	return (SUCCESS);
}

static int	count_redirection_out(t_token *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token->value[i])
	{
		if (token->value[i] == '>' && !(i && token->value[i - 1] == '>')
			&& token->value[i + 1] != '>' && !(i && token->value[i - 1] == '2')
			&& !(i && token->value[i - 1] == '&'))
		{
			count++;
			if (token->squote || token->dquote || (i != 0 && token->value[i
					- 1] == '\\'))
				break ;
			else
				return (count);
		}
		i++;
	}
	return (FAILED);
}

int	check_redirection_out(t_token *token, t_tokenlist *tokenlist)
{
	int		count;
	char	*symbol;

	count = count_redirection_out(token);
	if (!count)
		return (FAILED);
	symbol = ft_strdup(">");
	if (!symbol)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	split_token(tokenlist, symbol, token, count);
	if (token->type != TOK_SPLIT)
		return (FAILED);
	return (SUCCESS);
}
