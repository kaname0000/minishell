/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:16:38 by okaname           #+#    #+#             */
/*   Updated: 2025/03/26 00:33:10 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_gnl(char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

int	ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strndup_gnl(char *s, int n)
{
	int		len;
	char	*result;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen_gnl(s) < n)
		len = ft_strlen_gnl(s);
	else
		len = n;
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	s1_len = ft_strlen_gnl(s1);
	s2_len = ft_strlen_gnl(s2);
	str = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	if (s1 != NULL)
		ft_strlcat_gnl(str, s1, s1_len + 1);
	ft_strlcat_gnl(str, s2, s1_len + s2_len + 1);
	free(s1);
	return (str);
}

int	ft_strlcat_gnl(char *dst, char *src, int size)
{
	int	i;
	int	dst_len;
	int	src_len;

	if (!dst)
		dst_len = 0;
	else
		dst_len = ft_strlen_gnl(dst);
	src_len = ft_strlen_gnl(src);
	i = 0;
	if (size <= dst_len)
		return (size + src_len);
	while ((src[i] != '\0') && (i < size - dst_len - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}
