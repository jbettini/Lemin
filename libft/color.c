/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:52:50 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/08 00:02:07 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    setRandomizer() {
    srand(time(NULL));
}

t_color *getRandomColor(void) {
    t_color *color = malloc(sizeof(t_color));

    color->a = 256;
    color->r = rand() % 256;
    color->g = rand() % 256;
    color->b = rand() % 256;

    return color;
}