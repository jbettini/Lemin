/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 06:54:45 by jbettini          #+#    #+#             */
/*   Updated: 2024/03/29 07:49:58 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_time t;

void    startTimer(void) {
    t.debut = clock();
}

void    stopTimer(void) {
    t.fin = clock();
    printf("%stemps ecoulé : %f/sec\n%s", TXT_RED, ((double)(t.fin - t.debut) / CLOCKS_PER_SEC), FANCY_RESET);
    t.debut = 0;
    t.fin = 0;
}