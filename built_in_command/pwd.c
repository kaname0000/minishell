/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:31:40 by okaname           #+#    #+#             */
/*   Updated: 2025/03/24 20:54:26 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_pwd(void)
{
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)) != NULL)
		return (printf("%s\n", buf), 0);
	else
		return (perror("getcwd failed"), 1);
}
