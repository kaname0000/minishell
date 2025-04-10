/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:18:34 by okaname           #+#    #+#             */
/*   Updated: 2025/04/06 18:36:34 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_cd(char *path)
{
	if (chdir(path) == -1)
		perror("chdir failed");
	else
		ft_pwd();
	return (0);
}
