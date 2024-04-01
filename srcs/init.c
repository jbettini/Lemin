/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:18:31 by jbettini          #+#    #+#             */
/*   Updated: 2024/03/31 11:08:07 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemIn.h"

t_graph     *getEmptyGraph(void) {
    t_graph *graph = malloc(sizeof(t_graph) * 1);
    graph->rooms = NULL;
    graph->endRoom = NULL;
    graph->startRoom = NULL;
    graph->numRooms = 0;
    return graph;
}

t_simulation    *getEmptySimulation(void) {
    t_simulation    *simu = malloc(sizeof(t_simulation) * 1);
    simu->graph = getEmptyGraph();
    simu->ants = 0;
    simu->roomsNames = NULL;
    return simu;
}

t_room *roomCopy(t_room *src) {
    t_room *newRoom = malloc(sizeof(t_room));

    newRoom->name = ft_strdup(src->name);
    newRoom->posX = src->posX;
    newRoom->posY = src->posY;
    newRoom->isEnd = src->isEnd;
    newRoom->isStart = src->isStart;
    t_list *tmp = src->neigh;
    while (tmp) {
        ft_lstadd_back(&newRoom->neigh, ft_lstnew(ft_strdup(tmp->content)));
        tmp = tmp->next;
    }
    return newRoom;
}

t_room *roomConstructor(char *str) {
    char **splitArg = ft_split(str, ' ');
    t_room *newRoom = malloc(sizeof(t_room));
    newRoom->name = ft_strdup(splitArg[0]);
    newRoom->posX = ft_atoi(splitArg[1]);
    newRoom->posY = ft_atoi(splitArg[2]);
    newRoom->isEnd = false;
    newRoom->isStart = false;
    newRoom->neigh = NULL;
    newRoom->isSeen = NOT_SEEN;
    newRoom->isInqueue = false;
    newRoom->usedInPath = 0;
    newRoom->neighSize = 0;
    freeTab(splitArg);
    return newRoom;
}

