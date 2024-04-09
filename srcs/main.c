/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:21:39 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/08 23:56:18 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemIn.h"

int main (int ac, char **av) {
    (void)av;
    if (ac != 1)
        return invalidNumOfArg();
    startTimer();
    t_simulation	*simu = parseStdin();
    if (isIncompleteSimulation(simu))
        handleErrorWithoutStr(dataEnoughError);
    simu->visu = false;
    // // Find the fastest path
    createSolution(simu);

    
    //     //   Find all path possible

    
    
    //Solution
    
    handleAnts(simu->bestPath, simu);
    antsMoving(simu->antsQueue);
    stopTimer();
    // system("leaks lem-in");
    return 0;
}