/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ampersand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 20:07:55 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/02 19:59:32 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "check_tokentype.h"

// static int	count_ampersand(t_token *token, int c)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (token->value[i])
// 	{
// 		if (token->value[i] == c && token->value[i + 1] != '>')
// 		{
// 			count++;
// 			if (token->squote || token->dquote || (i != 0 && token->value[i
// 					- 1] == '\\'))
// 				break ;
// 			else
// 				return (count);
// 		}
// 		i++;
// 	}
// 	return (FAILED);
// }

// int	check_ampersand(t_token *token, int c, t_tokenlist *tokenlist)
// {
// 	int		count;
// 	char	*symbol;

// 	count = count_ampersand(token, c);
// 	if (!count)
// 		return (FAILED);
// 	symbol = (char *)malloc(sizeof(char) * 2);
// 	if (!symbol)
// 		free_tokenlist(tokenlist, NULL, NULL, FAILED);
// 	symbol[0] = (char)c;
// 	symbol[1] = '\0';
// 	split_token(tokenlist, symbol, token, count);
// 	if (token->type != TOK_SPLIT)
// 		return (FAILED);
// 	return (SUCCESS);
// }
