/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:19:15 by yookamot          #+#    #+#             */
/*   Updated: 2024/11/08 21:30:31 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int i)
{
	const char	*a = NULL;

	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)i)
			a = s;
		s++;
	}
	if (i == '\0')
		return ((char *)s);
	return ((char *)a);
}
