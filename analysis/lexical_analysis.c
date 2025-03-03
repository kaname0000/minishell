/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:08:50 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/03 19:58:37 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	if (s1[0] == '\0')
		return ((unsigned char)*s1 - (unsigned char)*s2);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	while (i < len1 && i < len2)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static int	check_literal(char *value)
{
	int	len;

	len = ft_strlen(value);
	if (value[0] == '\'')
	{
		if (value[len - 1] == '\'')
			return (0);
		return (1);
	}
	if (value[0] == '\"')
	{
		if (value[len - 1] == '\"')
			return (0);
		return (1);
	}
	return (1);
}

static int	check_invalid(char *value)
{
	int	len;

	len = ft_strlen(value);
	if (value[0] == '\'')
	{
		if (value[len - 1] != '\'')
			return (0);
		return (1);
	}
	if (value[0] == '\"')
	{
		if (value[len - 1] != '\"')
			return (0);
		return (1);
	}
	if (value[len - 1] == '\\')
		return (0);
	return (1);
}

//トークンのタイプ解析
static void	check_token(t_token token)
{
	if (!ft_strcmp(token->value, "&&") || !ft_strcmp(token->value, "||"))
		token->type = TOK_OPERATOR;
	else if (!ft_strcmp(token->value, "<") || !ft_strcmp(token->value, ">")
		|| !ft_strcmp(token->value, "<<") || !ft_strcmp(token->value, ">>"))
		token->type = TOK_REDIRECT;
	else if (!ft_strcmp(token->value, "|"))
		token->type = TOK_PIPE;
	else if (!check_literal(token->value))
		token->type = TOK_LITERAL;
	else if (!token->value || token->value[0] == '\0')
		token->type = TOK_END;
	else if (!check_invalid(token->value))
		token->type = TOK_INVALID;
	else
		token->type = TOK_IDENTIFIER;
}

//字句解析
void	lexical_analysis(t_tokenlist *tokenlist)
{
	int	i;
	int	j;

	i = 0;
	while (i < tokenlist->set_count)
	{
		j = 0;
		while (j < tokenlist->size[i])
		{
			check_token(tokenlist->token[i][j]);
			j++;
		}
		i++;
	}
}
