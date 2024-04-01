/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addStrToStrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:35:14 by jbettini          #+#    #+#             */
/*   Updated: 2024/03/22 23:06:31 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    **addStrToStrs(char *new, char **src) {
    char    **dst;
    int     i;

    i = -1;
    dst = malloc(sizeof(char *) * ft_strslen(src) + 2);
    while (src[++i])
        dst[i] = ft_strdup(src[i]);
    dst[i] = ft_strdup(new);
    dst[++i] = 0;
    return dst;
}