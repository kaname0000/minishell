/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:48:45 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/13 21:12:29 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <fcntl.h>

int	main(void)
{
	char		*input;
	char		*line;
	int			fd;
	t_tokenlist	*tokenlist;

	fd = open("test.txt", O_RDONLY);
	input = NULL;
	while ((line = get_next_line(fd)))
	{
		input = ft_strjoin_gnl(input, line);
		if (!input)
			return (1);
		free(line);
	}
	tokenlist = analysis(input);
	free(line);
	free(input);
	free_tokenlist(tokenlist, NULL, NULL, SUCCESS);
}
