/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:21:39 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/01 15:26:33 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemIn.h"

int main (int ac, char **av) {
    (void)av;
    if (ac != 1)
        return invalidNumOfArg();
    t_simulation	*simu = parseStdin();
    if (!simu)
        return ERROR;
    t_list *tmp = simu->graph->startRoom->neigh;
    // startTimer();
    while (tmp) {
        simu->graph->startRoom->isSeen = SEEN;
        pathFinding(simu, tmp->content);
        tmp = tmp->next;
        // ft_putstr("\n\n\n--------Queue is finish--------\n\n\n");
    }
    // printSimu(simu);
    // stopTimer();
    // check if one path exist else handle a error
    // system("leaks lem-in");
    // ft_lstiter_strs(simu->paths, ft_putsendl);
    return 0;
}