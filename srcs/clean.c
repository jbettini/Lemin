/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 23:26:32 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/17 05:07:24 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemIn.h"

void    cleanRoom(void *tRoom) {
    t_room *room = (t_room *)tRoom;
    ft_lstclear(&room->neigh, noFree);
    free(room->name);
    free(room);
    room = NULL;
    tRoom = NULL;
}

void    cleanGraph(void *tGraph) {
    t_graph *graph = (t_graph *)tGraph;
    ft_lstclear(&graph->rooms, cleanRoom);
    free(graph);
    graph = NULL;
    tGraph = NULL;
}


void    cleanPath(void *tPath) {
    t_path *path = (t_path *)tPath;
    ft_lstclear(&path->roomList, noFree);
    ft_lstclear(&path->multiRoom, noFree);
    ft_lstclear(&path->problematicRoom, noFree);
    ft_lstclear(&path->ants, noFree);
    if (path->color != NULL)
        free(path->color);
    free(path);
    path = NULL;
    tPath = NULL;
}

void    cleanPaths(void *tPaths) {
    t_list  *paths = (t_list *)tPaths;
    ft_lstclear(&paths, cleanPath);
}

void    cleanAnt(void *tAnt) {
    t_ant *ant = (t_ant *)tAnt;
    free(ant);
    ant = NULL;
    tAnt = NULL;    
}

void    cleanSimulation(t_simulation *simulation) {
    cleanGraph(simulation->graph);
    ft_lstclear(&simulation->roomsNames, free);
    ft_lstclear(&simulation->bestPath, noFree);
    ft_lstclear(&simulation->fasterPath, cleanPaths);
    ft_lstclear(&simulation->allPaths, cleanPaths);
    ft_lstclear(&simulation->antsQueue, cleanAnt);
    if (simulation->vColors)
        free(simulation->vColors);
    free(simulation);
    simulation = NULL;
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