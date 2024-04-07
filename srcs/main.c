/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:21:39 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/08 01:37:51 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemIn.h"

int main (int ac, char **av) {
    (void)av;
    if (ac != 1)
        return invalidNumOfArg();
    // startTimer();
    t_simulation	*simu = parseStdin();
    if (isIncompleteSimulation(simu))
        return dataEnoughError();
    simu->visu = false;
    // // Find the fastest path
    createSolution(simu);

    
    //     //   Find all path possible
    
    // t_list *tmp = simu->graph->startRoom->neigh;

    // while (tmp) {
    //     simu->graph->startRoom->isSeen = SEEN;
    //     pathFinding(simu, tmp->content);
    //     tmp = tmp->next;
    // }
    // initProblematicNodes(&(simu->allPaths));
    
    
    

    // Step : need to modify problematic nodes to specify an 
                    // node is problematic only if is used in a path create with another start node neighbors
    // Step : crete best flow solution
    
    // Step : chose between flow and fastness
    
    
    //Solution
    
    handleAnts(simu->bestPath, simu);
    antsMoving(simu->antsQueue);
    system("leaks lem-in");
    return 0;
}