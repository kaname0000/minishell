/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:17:29 by yookamot          #+#    #+#             */
/*   Updated: 2024/11/08 14:29:47 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdint.h>

void	*ft_calloc(size_t num, size_t size)
{
	void	*array;
	size_t	n;

	if (num != 0 && size > SIZE_MAX / num)
		return (NULL);
	n = num * size;
	array = malloc(n);
	if (!array)
		return (NULL);
	return (ft_memset(array, 0, n));
}
