/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:46:29 by okaname           #+#    #+#             */
/*   Updated: 2025/04/13 16:31:09 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_export(t_mini *mini, int count)
{
	int	count_a;

	count_a = count_array(mini->cmd[count]->cmd);
	if (count_a == 1)
		print_sorted_env(mini->var_env);
	else
		printf("exportだよ\n");
	return (0);
}
