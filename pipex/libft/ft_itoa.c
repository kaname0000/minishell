/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:25:44 by yookamot          #+#    #+#             */
/*   Updated: 2024/10/28 18:24:52 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_num_length(int n)
{
	int	i;

	if (n == 0)
		return (1);
	if (n >= 0)
		i = 0;
	else
		i = 1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*result;
	long int	num;

	len = ft_get_num_length(n);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (n == 0)
		result[0] = '0';
	num = n;
	if (num < 0)
	{
		result[0] = '-';
		num = -num;
	}
	while (len > 0 && num > 0)
	{
		result[--len] = num % 10 + '0';
		num /= 10;
	}
	return (result);
}
