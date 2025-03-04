/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:19:34 by okaname           #+#    #+#             */
/*   Updated: 2025/03/04 17:48:18 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strtok(char *str, const char *delim)
{
	static char	*saveptr = NULL;
	char		*token_start;

	if (str != NULL)
		saveptr = str;
	if (saveptr == NULL)
		return (NULL);
	while (*saveptr && ft_strchr(delim, *saveptr))
		saveptr++;
	if (*saveptr == '\0')
		return (NULL);
	token_start = saveptr;
	while (*saveptr && !ft_strchr(delim, *saveptr))
		saveptr++;
	if (*saveptr)
	{
		*saveptr = '\0';
		saveptr++;
	}
	return (token_start);
}

// void	test_ft_strtok(char *input, const char *delim)
// {
// 	char	*copy1;
// 	char	*copy2;

// 	copy1 = strdup(input);
// 	copy2 = strdup(input);
// 	char *token1, *token2;
// 	printf("Testing input: '%s' with delimiter: '%s'\n", input, delim);
// 	printf("ft_strtok output: ");
// 	token1 = ft_strtok(copy1, delim);
// 	while (token1)
// 	{
// 		printf("[%s] ", token1);
// 		token1 = ft_strtok(NULL, delim);
// 	}
// 	printf("\n");
// 	printf("strtok output:    ");
// 	token2 = strtok(copy2, delim);
// 	while (token2)
// 	{
// 		printf("[%s] ", token2);
// 		token2 = strtok(NULL, delim);
// 	}
// 	printf("\n\n");
// 	free(copy1);
// 	free(copy2);
// }

// int	main(void)
// {
// 	test_ft_strtok("hello world this is a test", " ");
// 	test_ft_strtok(",,hello,,world,,,", ",");
// 	test_ft_strtok("abc-def-ghi", "-");
// 	test_ft_strtok("one::two:::three", ":");
// 	test_ft_strtok("    leading and trailing spaces    ", " ");
// 	return (0);
// }
