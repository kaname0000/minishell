/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_invalid_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:37:35 by yookamot          #+#    #+#             */
/*   Updated: 2025/06/12 17:48:42 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	count_invalid_env_len(char *value)
{
	int	i;
	int	len;

	i = 0;
	while (value[i] != '$')
		i++;
	if (!value[i + 1] || (!ft_isalpha(value[i + 1]) && value[i + 1] != '_'))
		return (0);
	len = 1;
	while (value[i + len])
	{
		if (!ft_isalnum(value[i + len]) && value[i + len] != '_')
			break ;
		len++;
	}
	return (len);
}

static char	*reshape_value(char *value, int len, t_tokenset *tokenset)
{
	char	*new;
	int		i;
	int		j;
	int		new_len;

	new_len = ft_strlen(value) - len;
	if (new_len <= 0)
		new_len = 1;
	new = (char *)malloc(sizeof(char) * new_len);
	if (!new)
		free_tokenset(tokenset, FAILED);
	i = 0;
	j = 0;
	while (value[j] && value[j] != '$')
		new[i++] = value[j++];
	j += len;
	while (value[j])
		new[i++] = value[j++];
	if (i == 0 || new_len > i)
		new[i++] = '\0';
	else
		new[i] = '\0';
	return (new);
}

void	remove_invalid_env(t_tokenset *tokenset)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	while (i < tokenset->count)
	{
		if ((tokenset->token[i]->type == TOK_DQUOTE_IN
				|| tokenset->token[i]->type == TOK_WORD)
			&& ft_strchr(tokenset->token[i]->value, '$'))
		{
			len = count_invalid_env_len(tokenset->token[i]->value);
			if (len > 0)
			{
				new = reshape_value(tokenset->token[i]->value, len, tokenset);
				free(tokenset->token[i]->value);
				tokenset->token[i]->value = new;
				continue ;
			}
		}
		i++;
	}
}
