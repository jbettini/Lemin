/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaksManager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:33:04 by jbettini          #+#    #+#             */
/*   Updated: 2024/03/21 19:47:18 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void    leaksManager(int mode, void *ptr){
    static  t_list *allPtr;
    if (mode == ADD) {
        t_list  *tmp = allPtr;
        while (tmp) {
            if (tmp->content == ptr)
                return ;
            tmp = tmp->next;
        }
        ft_lstadd_back(&allPtr ,ft_lstnew(ptr));
    }
    else if (mode == DELETE)
        ft_lstclear(&allPtr, free);
}