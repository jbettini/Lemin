/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:21:39 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/16 20:08:01 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemIn.h"

// t_simulation *simu;

int main (int ac, char **av) {
    (void)av;
    if (ac != 1)
        return invalidNumOfArg();
    startTimer();
    t_simulation	*simu = parseStdin();
    // simu = parseStdin();
    if (isIncompleteSimulation(simu))
        handleErrorWithoutStr(dataEnoughError);
    simu->visu = false;
    createSolution(simu);
    handleAnts(simu->bestPath, simu);
    antsMoving(simu->antsQueue);
    stopTimer();
    cleanSimulation(simu);
    // system("leaks lem-in");
    return 0;
}