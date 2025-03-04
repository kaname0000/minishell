/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:57:36 by yookamot          #+#    #+#             */
/*   Updated: 2024/10/25 17:13:44 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	a;
	size_t	b;

	a = 0;
	if (!s1 || !s2)
		return (NULL);
	if (*s2 == '\0')
		return ((char *)s1);
	if (n == 0)
		return (NULL);
	while (s1[a] != '\0' && a < n)
	{
		b = 0;
		while (s1[a + b] == s2[b] && a + b < n && s2[b] != '\0')
			b++;
		if (b == ft_strlen(s2))
			return ((char *)(s1 + a));
		a++;
	}
	return (NULL);
}
