/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 04:46:37 by yookamot          #+#    #+#             */
/*   Updated: 2024/10/25 05:29:19 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_head;
	t_list	*new_node;

	new_head = NULL;
	if (lst == NULL || f == NULL)
		return (NULL);
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		if (!new_head)
			new_head = new_node;
		else
			ft_lstadd_back(&new_head, new_node);
		lst = lst->next;
	}
	return (new_head);
}
