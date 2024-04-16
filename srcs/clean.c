/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 23:26:32 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/16 20:16:35 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemIn.h"

void    cleanRoom(void *tRoom) {
    if (tRoom == NULL)
        return ;
    t_room *room = (t_room *)tRoom;
    ft_lstclear(&room->neigh, noFree);
    free(room);
    room = NULL;
    tRoom = NULL;
}

void    cleanGraph(void *tGraph) {
    if (tGraph == NULL)
        return ;
    t_graph *graph = (t_graph *)tGraph;
    ft_lstclear(&graph->rooms, cleanRoom);
    free(graph);
    graph = NULL;
    tGraph = NULL;
}

void    cleanAnt(void *tAnt) {
    if (tAnt == NULL)
        return ;
    t_ant *ant = (t_ant *)tAnt;
    ft_lstclear(&ant->roomList, noFree);
    // Maybe need to free colors here
    free(ant);
    ant = NULL;
    tAnt = NULL;    
}

void    cleanPath(void *tPath) {
    t_path *path = (t_path *)tPath;
    ft_lstclear(&path->roomList, noFree);
    ft_lstclear(&path->multiRoom, noFree);
    // ft_lstclear(&path->problematicRoom, noFree);
    // ft_lstclear(&path->ants, noFree);
    // Maybe need to clean colors here
    // free(path);
    // path = NULL;
    // tPath = NULL;
}

void    cleanSimulation(t_simulation *simulation) {
    cleanGraph(simulation->graph);
    ft_lstclear(&simulation->roomsNames, free);

    
    // ft_lstclear(&simulation->fasterPath, cleanPath);
    // ft_lstclear(&simulation->allPaths, cleanPath);
    // ft_lstclear(&simulation->bestPath, noFree);
    // ft_lstclear(&simulation->antsQueue, cleanAnt);
    // free(simulation);
    // simulation = NULL;
    if (simulation != NULL)
        return;
}


void    safeFree(void *ptr) {
    if (ptr)
        free(ptr);
}

void    freeTab(char **tab) {
    int i = 0;
    while(tab[i])
        safeFree(tab[i++]);
    safeFree(tab);
}