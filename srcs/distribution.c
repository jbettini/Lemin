/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:30:19 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/16 20:43:07 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemIn.h"

void simplePop(t_list **list) {
    if (*list == NULL)
        return;

    t_list *first = *list;
    *list = first->next;
    first->next = NULL;
    free(first);
}

int     getNextHigherSize(t_list *p, int size) {
    t_path  *path = NULL;
    t_list *tmp = p;
    while (tmp) {
        path = (t_path *)tmp->content;
        if (path->pathSize + path->antsInPath > size)
            return (path->pathSize + path->antsInPath);
        tmp = tmp->next;
    }
    return (path->pathSize + path->antsInPath);
}

t_ant *getAnt(int currentAnt, t_path **p) {
    t_ant   *ret = malloc(sizeof(t_ant));
    ret->num = currentAnt;
    ret->roomList = (*p)->roomList;
    ret->path = *p;
    ret->moved = false;
    ret->color = (*p)->color;
    ret->inQueue = false;
    ret->reached = false;
    ret->ended = false;
    t_room  *r = (*p)->roomList->content;
    ret->posX = (float)r->posX;
    ret->posY = (float)r->posY;
    ret->distX = 0;
    ret->distY = 0;
    return ret;
}

void     fill(t_list *paths, int totalAnts, int currentAnt, t_simulation *s) {
    t_list      *tmp = NULL;
    t_path      *currentPath = NULL;
    while (totalAnts > 0) {
        tmp = paths;
        currentPath = (t_path *)paths->content;
        while (tmp && totalAnts > 0) {
            currentPath = (t_path *)tmp->content;
            currentPath->antsInPath++;
            ft_lstadd_back(&currentPath->ants , ft_lstnew(getAnt(currentAnt, &currentPath)));
            // ft_lstadd_back(&s->antsHandled , ft_lstnew(getAnt(currentAnt, &currentPath)));
            totalAnts--;
            currentAnt++;
            tmp = tmp->next;
        }
    }
    if(s)
        return;
}

t_list    *setQueueAnts(t_list   *paths) {
    t_list  *p = NULL;;
    t_list  *antsQueue = NULL;
    t_list  *ret = NULL;
    t_path  *path = NULL;
    do
    {
        p = paths;
        while (p) {
            path = p->content;
            antsQueue = path->ants;
            if (ft_lstsize(antsQueue) > 0) {
                ft_lstadd_back(&ret, ft_lstnew(antsQueue->content));
                simplePop(&path->ants);
            }
            p = p->next;
        }
    } while (ft_lstsize(((t_path *)paths->content)->ants));
    return ret;
}

void    handleAnts(t_list   *paths, t_simulation *s) {
    int         nextSize = 0;
    int         currentSize = 0;
    int         currentAnt = 1;
    int         totalAnts = s->ants;
    t_list      *tmp = NULL;
    t_path      *currentPath = NULL;
    while (totalAnts > 0) {
        tmp = paths;
        currentPath = (t_path *)paths->content;
        currentSize = currentPath->pathSize + currentPath->antsInPath;
        nextSize = getNextHigherSize(paths, currentSize);
        if (nextSize == currentSize) {
            fill(paths, totalAnts, currentAnt, s);
            s->antsQueue = setQueueAnts(s->bestPath);
            return ;
        }
        while (tmp) {

            currentPath = (t_path *)tmp->content;
            if (currentPath->pathSize == nextSize)
                break ;
            currentPath->antsInPath++;
            ft_lstadd_back(&currentPath->ants , ft_lstnew(getAnt(currentAnt, &currentPath)));
            totalAnts--;
            currentAnt++;
            tmp = tmp->next;
        }
    }
    s->antsQueue = setQueueAnts(s->bestPath);
}

void    printMove(t_ant *ant){
    ft_putstr("L");
    ft_putnbr(ant->num);
    ft_putstr("-");
    t_room *r = ant->roomList->content;
    ft_putstr(r->name);
    ft_putstr(" ");
}


void    resetForLoop(t_list *queue){
    t_list  *tmp = queue;
    t_ant   *ant = NULL;
    while (tmp) {
        ant = tmp->content;
        ant->moved = false;
        tmp = tmp->next;
    }
    // ft_putstr("\n");
}

void    headToBack(t_list   **list) {
    if (*list == NULL)
        return;

    t_list *first = *list;
    *list = first->next;
    first->next = NULL;
    ft_lstadd_back(list, first);
}

bool    moveForward(t_ant **ant) {
    (*ant)->moved = true;
    (*ant)->path->full = false;
    (*ant)->roomList = (*ant)->roomList->next;
    // printMove(*ant);
    if ((*ant)->roomList->next == NULL)
        return true;
    return false;
}

void    antsMoving(t_list   *ants) {
    t_list  *tmp = ants;
    t_list  *queue = NULL;
    t_ant   *ant = NULL;
    int     numOfLine = 0;
    do
    {
        while (tmp) {
            ant = tmp->content;
            if (ant->path->full == true)
                break;
            ft_lstadd_back(&queue, ft_lstnew(ant));
            ant->path->full = true;
            tmp = tmp->next;
        }
        while (queue) {
            ant = queue->content;
            if (ant->moved == true)
                break ;
            if (moveForward(&ant))
                simplePop(&queue);
            else 
                headToBack(&queue);
        }
        resetForLoop(queue);
        numOfLine++;
    } while (ft_lstsize(queue) > 0);
    ft_putendl(FANCY_RESET);
    ft_putstr(TXT_GREEN);
    ft_putstr("Solved in : ");
    ft_putnbr(numOfLine);
    ft_putendl(FANCY_RESET);
}