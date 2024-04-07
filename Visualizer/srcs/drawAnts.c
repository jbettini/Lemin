#include "visualizer.h"

bool closeToRoom(t_ant *a) {
    t_room *nextRoom = a->roomList->next->content;
    float distX = nextRoom->posX - a->posX;
    float distY = nextRoom->posY - a->posY;
    if (distX <= 0.1 && distY <= 0.1)
        return true;
    return false;
}

bool updateAntPosition(t_ant *ant) {
    ant->posX += ant->distX * SPEED;
    ant->posY += ant->distY * SPEED;
    return closeToRoom(ant);
}

bool    updatePos(t_ant **ant) {
    (*ant)->moved = true;
    (*ant)->path->full = false;
    if (updateAntPosition(*ant)) {
        (*ant)->roomList = (*ant)->roomList->next;
        t_room *r = (*ant)->roomList->content;
        (*ant)->posX = r->posX;
        (*ant)->posY = r->posY;
        if ((*ant)->roomList->next == NULL) {
            (*ant)->ended = true;
            return true;
        }
        (*ant)->reached = true;
    }
    return false;
}

void    resetLoop(t_visu *v) {
    t_list  *tmp = v->queue;
    t_ant   *ant = NULL;
    bool    allReached = true;
    if (!tmp)
        return ;
    while (tmp) {
        ant = tmp->content;
        ant->moved = false;
        if (ant->reached == false)
            allReached = false;
        tmp = tmp->next;
    }
    if (allReached) {
        tmp = v->queue;
        v->readyToEnqueue = true;
        while (tmp) {
            ant = tmp->content;
            ant->reached = false;
            tmp = tmp->next;
        }
    }
}

void    handleAntsPosition(t_list   *ants, t_visu *v) {
    t_list  *tmp = ants;
    t_ant   *ant = NULL;

    // enqueue next ants
    if (v->readyToEnqueue == true) {
        v->readyToEnqueue = false;
        while (tmp) {
            ant = tmp->content;
            if (ant->ended) {
                tmp = tmp->next;
                continue ;
            }
            else if (ant->inQueue) {
                t_room *nextRoom = ant->roomList->next->content;
                ant->distX = nextRoom->posX - ant->posX;
                ant->distY = nextRoom->posY - ant->posY;
                tmp = tmp->next;
                continue ;
            }
            if (ant->path->full == true)
                break;
            t_room *nextRoom = ant->roomList->next->content;
            ant->distX = nextRoom->posX - ant->posX;
            ant->distY = nextRoom->posY - ant->posY;
            ft_lstadd_back(&(v->queue), ft_lstnew(ant));
            ant->path->full = true;
            ant->inQueue = true;
            tmp = tmp->next;
        }
        
    }


    while ((v->queue)) {
        ant = (v->queue)->content;
        if (ant->moved == true)
            break ;
        if (updatePos(&ant))
            simplePop(&(v->queue));
        else 
            headToBack(&(v->queue));
    }

    // printf("________________\n");
    // printAntsInList(v->queue);
    // printf("________________\n");
    resetLoop(v);
}