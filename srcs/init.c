/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:18:31 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/18 23:15:02 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemIn.h"

t_vcolors        *getVcolors(void) {
    t_vcolors   *ret = malloc(sizeof(t_vcolors));
    ret->background = getGreyColor();
    ret->link = getWhiteColor();
    ret->start = getRedColor();
    ret->end = getGreenColor();
    ret->rooms = getBlueColor();
    return ret;
}

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
    simu->allPaths = NULL;
    simu->fasterPath = NULL;
    simu->bestPath = NULL;
    simu->vColors = NULL;
    return simu;
}

t_path          *getEmptyPath(void) {
    t_path  *p = malloc(sizeof(t_path));
    p->roomList = NULL;
    p->multiRoom = NULL;
    p->problematicRoom = NULL;
    p->unique = false;
    p->pathSize = 0;
    p->heuristic = -42000;
    return p;
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
    t_room *newRoom = NULL;
    if (ft_strslen(splitArg) != 3) {
        freeTab(splitArg);
        return newRoom;
    }
    else if (!isValidNum(splitArg[1]) && !isValidNum(splitArg[2])) {
        freeTab(splitArg);
        return newRoom;
    }
    else {
        newRoom = malloc(sizeof(t_room));
        newRoom->name = ft_strdup(splitArg[0]);
        newRoom->posX = ft_atoi(splitArg[1]);
        newRoom->posY = ft_atoi(splitArg[2]);
        newRoom->isEnd = false;
        newRoom->isStart = false;
        newRoom->neigh = NULL;
        newRoom->isSeen = NOT_SEEN;
        newRoom->isInqueue = false;
        newRoom->upUsed = false;
        newRoom->usedInPath = 0;
        newRoom->neighSize = 0;
    }
    freeTab(splitArg);
    return newRoom;
}

void            initProblematicNodes(t_list **allPaths){
    t_list  *paths = *allPaths;
    t_list  *path = NULL;
    t_list  *multiNode = NULL;
    t_room  *roomTmp = NULL;
    t_path  *tmp = NULL;
    int     pbNodes = 0;
    while (paths) {
        path = (t_list *)paths->content;
        while (path) {
            tmp = (t_path *)path->content;
            multiNode = tmp->multiRoom;
            while (multiNode) {
                roomTmp = (t_room *)multiNode->content;
                if (roomTmp->usedInPath > 1) {
                    pbNodes++;
                    ft_lstadd_back(&tmp->problematicRoom, ft_lstnew(roomTmp));
                    // if (ft_lstsize(*allPaths) / 2 <= roomTmp->usedInPath)
                    //     tmp->totalWeigh *= roomTmp->usedInPath;
                    // else
                    //     tmp->totalWeigh /= roomTmp->usedInPath;
                }
                multiNode = multiNode->next;
            }
            tmp->numsOfPbRooms = pbNodes;
            tmp->heuristic = 1 / (tmp->pathSize + (tmp->numsOfPbRooms * 1.5));
            // tmp->heuristic = 1 / ((tmp->pathSize )+ ((tmp->numsOfPbRooms + tmp->totalWeigh) * 2.0));
            if (pbNodes == 0)
                tmp->unique = true;
            pbNodes = 0;
            path = path->next;
        }
        paths = paths->next;
    }
}

