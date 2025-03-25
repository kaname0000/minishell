/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:27:34 by okaname           #+#    #+#             */
/*   Updated: 2025/03/26 00:34:01 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_make_newline_pos(char **buffer, char *tmp, int byte)
{
	if (byte == -1 || (byte == 0 && *buffer == NULL))
	{
		free(*buffer);
		*buffer = NULL;
		free(tmp);
		return (NULL);
	}
	tmp[byte] = '\0';
	*buffer = ft_strjoin_gnl(*buffer, tmp);
	if (*buffer == NULL)
	{
		free(tmp);
		return (NULL);
	}
	return (*buffer);
}

static char	*ft_make_buffer(char **buffer, int fd)
{
	int		byte;
	char	*tmp;
	char	*newline_position;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (tmp == NULL)
		return (NULL);
	byte = 1;
	newline_position = ft_strchr_gnl(*buffer, '\n');
	while (newline_position == NULL && byte > 0)
	{
		byte = read(fd, tmp, BUFFER_SIZE);
		if (ft_make_newline_pos(buffer, tmp, byte) == NULL)
			return (NULL);
		newline_position = ft_strchr_gnl(*buffer, '\n');
	}
	free(tmp);
	return (newline_position);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*newline_position;
	char		*result;
	char		*new_buffer;

	newline_position = ft_make_buffer(&(buffer), fd);
	if (newline_position == NULL || *(newline_position + 1) == '\0')
	{
		if (buffer)
		{
			result = ft_strndup_gnl(buffer, ft_strlen_gnl(buffer));
			free(buffer);
			buffer = NULL;
			return (result);
		}
		return (NULL);
	}
	result = ft_strndup_gnl(buffer, (newline_position - buffer + 1));
	new_buffer = ft_strndup_gnl(newline_position + 1,
			ft_strlen_gnl(newline_position + 1));
	if (new_buffer == NULL)
		return (NULL);
	free(buffer);
	buffer = new_buffer;
	return (result);
}

// int	main(void)
// {
// 	char	*line;

// 	// int		fd;
// 	line = get_next_line(0);
// 	while (line != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(0);
// 	}
// 	printf("%s", line);
// 	free(line);
// 	// close(fd);
// 	return (0);
// }
