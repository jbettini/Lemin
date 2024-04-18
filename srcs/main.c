/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:21:39 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/18 23:10:53 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemIn.h"

int main (int ac, char **av) {
    (void)av;
    if (ac != 1)
        return invalidNumOfArg();
    // startTimer();
    t_simulation	*simu = parseStdin(false);
    if (isIncompleteSimulation(simu))
        handleErrorWithoutStr(dataEnoughError);
    createSolution(simu);
    handleAnts(simu->bestPath, simu);
    antsMoving(simu->antsQueue);
    // stopTimer();
    cleanSimulation(simu);
    return 0;
}