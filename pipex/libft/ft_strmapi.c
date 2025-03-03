/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:04:00 by yookamot          #+#    #+#             */
/*   Updated: 2024/11/08 21:47:33 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*result;
	size_t	size;

	if (!s || !f)
		return (NULL);
	size = (int)ft_strlen(s);
	i = 0;
	result = (char *)malloc(size + 1);
	if (!result)
		return (NULL);
	while (i < size)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
