/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_custom.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:18:05 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/24 18:11:12 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static size_t	ft_word_count(const char *s, char c)
{
	size_t	word_count;
	size_t	i;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			word_count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (word_count);
}

static char	**ft_free(char **result, size_t word_count)
{
	while (word_count > 0)
		free(result[--word_count]);
	free(result);
	return (NULL);
}

static void	ft_strcpy_len(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static char	**ft_split_words(char **result, const char *s, char c,
		size_t word_count)
{
	size_t	i;
	size_t	word_len;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			word_len = 0;
			while (s[i + word_len] && s[i + word_len] != c)
				word_len++;
			result[word_count] = (char *)malloc(sizeof(char) * (word_len + 1));
			if (!result[word_count])
				return (ft_free(result, word_count));
			ft_strcpy_len(result[word_count++], &s[i], word_len);
			i += word_len;
		}
		else
			i++;
	}
	result[word_count] = ft_strdup("\n");
	if (!result[word_count])
		return (ft_free(result, word_count));
	return (result[++word_count] = NULL, result);
}

char	**ft_split_custom(char *s, t_tokenlist *tokenlist, int i)
{
	char	**result;
	size_t	count;

	if (i == tokenlist->set_count - 1)
		return (ft_split_for_tab(s));
	if (!s)
		return (NULL);
	count = ft_word_count(s, ' ') + ft_word_count(s, '\t');
	result = (char **)malloc(sizeof(char *) * (count + 2));
	if (!result)
		return (NULL);
	ft_split_words(result, s, ' ', 0);
	ft_split_words(result, s, '\t', 0);
	return (result);
}
