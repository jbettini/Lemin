/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:31:37 by jbettini          #+#    #+#             */
/*   Updated: 2024/03/25 16:35:02 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*li;

	li = *alst;
	if (alst)
	{
		if (*alst)
		{
			while (li->next)
				li = li->next;
			// if (new)
			// 	new->prev = li;
			li->next = new;
		}
		else {
			*alst = new;
		}
	}
}

// void	ft_lstadd_back(t_list **alst, t_list *new)
// {
// 	t_list	*last;

// 	if (!alst || !new)
// 		return ;
// 	if (!*alst)
// 	{
// 		*alst = new;
// 		return ;
// 	}
// 	last = ft_lstlast(*alst);
// 	last->next = new;
// 	new->prev = last;
// }
