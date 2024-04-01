/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:06:08 by jbettini          #+#    #+#             */
/*   Updated: 2024/03/29 07:27:17 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

void	ft_lstiter_strs(t_list *lst, void (*f)(char **))
{
	int i;
	
	i = 0;
	while (lst)
	{
		ft_putstr("str ");
		ft_putnbr(i++);
		ft_putstr("\n");
		(*f)(lst->content);
		lst = lst->next;
		ft_putstr("\n");
	}
}
