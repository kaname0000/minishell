/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:48:45 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/04 20:59:59 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "fcntl.h"

static void	free_all_value(t_tokenlist *tokenlist)
{
	int	x;
	int	y;

	x = 0;
	while (x < tokenlist->set_count)
	{
		y = 0;
		while (y < tokenlist->size[x])
		{
			free(tokenlist->token[x][y].value);
			y++;
		}
		x++;
	}
}

static void	free_tokenlist(t_tokenlist *tokenlist)
{
	free_all_value(tokenlist);
	free_array((void **)tokenlist->token);
	free(tokenlist->size);
	free(tokenlist);
}

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
	free(input);
	free_tokenlist(tokenlist);
}
