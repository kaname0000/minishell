/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:48:45 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/10 16:43:39 by yookamot         ###   ########.fr       */
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
	printf("set_count = %d, token_count = {%d, %d}\n", tokenlist->set_count,
		tokenlist->token_count[0], tokenlist->token_count[1]);
	free(line);
	free(input);
	free_tokenlist(tokenlist, NULL, NULL, SUCCESS);
}
