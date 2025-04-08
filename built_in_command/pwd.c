/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:31:40 by okaname           #+#    #+#             */
/*   Updated: 2025/04/08 21:59:47 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_pwd(t_mini *mini, int count)
{
	char	buf[1024];

	(void)mini;
	(void)count;
	if (getcwd(buf, sizeof(buf)) != NULL)
		return (printf("%s\n", buf), 0);
	return (perror("getcwd failed"), 1);
}
