/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:10:58 by okaname           #+#    #+#             */
/*   Updated: 2025/03/03 17:53:02 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// arg={"/bin/ls",[option],NULL}
int	ls(char *arg[], char *envp[])
{
	if (execve(arg[0], arg, envp) == -1)
		perror("execve");
	return (1);
}
