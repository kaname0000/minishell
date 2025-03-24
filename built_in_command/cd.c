/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:18:34 by okaname           #+#    #+#             */
/*   Updated: 2025/03/20 04:26:17 by okaname          ###   ########.fr       */
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

// int	main(int argc, char *argv[])
// {
// 	ft_cd(argv[1]);
// 	return (0);
// }
