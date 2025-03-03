/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 04:25:30 by yookamot          #+#    #+#             */
/*   Updated: 2024/10/25 15:47:09 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*x;
	t_list	*y;

	if (lst == NULL || del == NULL)
		return ;
	x = *lst;
	while (x)
	{
		y = x->next;
		del(x->content);
		free(x);
		x = y;
	}
	*lst = NULL;
}
