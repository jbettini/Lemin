/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 23:26:32 by jbettini          #+#    #+#             */
/*   Updated: 2024/03/25 07:28:14 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemIn.h"

void    cleanRoom();

void    cleanGraph();

void    cleanSimulation();


void    safeFree(void *ptr) {
    if (ptr)
        free(ptr);
}

void    freeTab(char **tab) {
    for (int i = 0; tab[i]; i++)
        safeFree(tab[i]);
    safeFree(tab);
}