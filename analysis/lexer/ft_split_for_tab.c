/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_for_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:11:41 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/24 18:15:35 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	ft_split_count(char const *str)
{
	int	word_count;
	int	i;
	int	flag;

	if (str == NULL)
		return (0);
	word_count = 0;
	i = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == ' ' || str[i] == '\t') && flag)
		{
			word_count++;
			flag = 0;
		}
		if (str[i] != ' ' && str[i] != '\t')
			flag = 1;
		i++;
	}
	if (flag)
		word_count++;
	return (word_count);
}

static int	ft_strlen_alp(char const *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] == ' ' || s[i] == '\t')
	{
		i++;
	}
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t')
	{
		i++;
		j++;
	}
	return (j);
}

static char	*ft_strdup_alp(char const *src, int num)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *)malloc((num + 1) * sizeof(char));
	if (dest == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < num)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	ft_all_free(char **strs, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**ft_split_for_tab(char const *s)
{
	char	**strs;
	int		split_count;
	int		i;
	int		j;

	i = 0;
	j = 0;
	split_count = ft_split_count(s);
	strs = (char **)malloc(sizeof(char *) * (split_count + 1));
	if (strs == NULL)
		return (NULL);
	while (i < split_count)
	{
		while (s[j] == ' ' || s[j] == '\t')
			j++;
		strs[i] = ft_strdup_alp(&s[j], ft_strlen_alp(&s[j]));
		if (strs[i++] == NULL)
		{
			ft_all_free(strs, i - 1);
			return (NULL);
		}
		j += ft_strlen_alp(&s[j]);
	}
	strs[i] = NULL;
	return (strs);
}
