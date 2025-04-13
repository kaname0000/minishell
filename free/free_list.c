/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:04:48 by okaname           #+#    #+#             */
/*   Updated: 2025/04/13 17:32:44 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_list(t_env *head)
{
	t_env	*tmp;

	while (head != NULL)
	{
		tmp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = tmp;
	}
}
