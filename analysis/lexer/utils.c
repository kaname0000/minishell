/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:19:30 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/13 20:29:17 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	a;
	size_t	b;

	a = 0;
	if (!s1 || !s2)
		return (NULL);
	if (*s2 == '\0')
		return ((char *)s1);
	while (s1[a] != '\0')
	{
		b = 0;
		while (s1[a + b] == s2[b] && s2[b] != '\0')
			b++;
		if (b == ft_strlen(s2))
			return ((char *)(s1 + a));
		a++;
	}
	return (NULL);
}
