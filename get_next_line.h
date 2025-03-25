/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:34:21 by okaname           #+#    #+#             */
/*   Updated: 2025/03/26 00:33:34 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_strchr_gnl(char *s, int c);
int		ft_strlen_gnl(char *s);
char	*ft_strndup_gnl(char *s, int n);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_strlcat_gnl(char *dst, char *src, int size);

#endif
