/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:02:36 by okaname           #+#    #+#             */
/*   Updated: 2025/05/24 00:00:47 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_mini(t_mini *mini)
{
	free_list(mini->var_env);
	free_cmd(mini->cmd);
	free(mini->input);
}
