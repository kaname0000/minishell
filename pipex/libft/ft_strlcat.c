/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:40:04 by yookamot          #+#    #+#             */
/*   Updated: 2024/11/08 21:28:34 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	c;
	size_t	i;

	if (!dest || !src)
		return (-1);
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size == 0 || dest_len >= size)
		return (src_len + size);
	c = size - dest_len - 1;
	i = 0;
	while (i < c && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
