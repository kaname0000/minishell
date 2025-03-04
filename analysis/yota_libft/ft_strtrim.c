/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:05:38 by yookamot          #+#    #+#             */
/*   Updated: 2024/11/08 14:20:32 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_get_start(const char *s1, const char *set)
{
	size_t	start;
	size_t	i;

	start = 0;
	while (s1[start] != '\0')
	{
		i = 0;
		while (s1[start] != set[i] && set[i] != '\0')
			i++;
		if (set[i] == '\0')
			return (start);
		start++;
	}
	return (start);
}

size_t	ft_get_end(const char *s1, const char *set)
{
	size_t	end;
	size_t	i;
	size_t	len;

	len = ft_strlen(s1);
	if (len == 0)
		return (0);
	end = len - 1;
	while (end && end != (size_t)-1)
	{
		i = 0;
		while (s1[end] != set[i] && set[i])
			i++;
		if (set[i] == '\0')
			return (end);
		end--;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*result;
	size_t	start;
	size_t	end;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	if (!set || !*set)
		return (ft_strdup(s1));
	if (!*s1)
		return (ft_strdup(""));
	start = ft_get_start(s1, set);
	end = ft_get_end(s1, set);
	if (start > end)
		return (ft_strdup(""));
	result = (char *)malloc(end - start + 2);
	if (!result)
		return (NULL);
	while (start <= end)
		result[i++] = s1[start++];
	result[i] = '\0';
	return (result);
}
