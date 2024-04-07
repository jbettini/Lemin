#include "lemIn.h"

void custom_pop(t_list **list, t_list **poped) {
    if (*list == NULL)
        return;

    t_list *first = *list;
    *list = first->next;
    first->next = NULL;
    ft_lstadd_back(poped, first);
}

void    resetGraph(t_simulation **s){
    t_graph *g = (*s)->graph;
    t_room  *r = NULL;
    t_list  *tmp = g->rooms;

    while (tmp) {
        r = (t_room *)tmp->content;
        r->isSeen = NOT_SEEN;
        r->isInqueue = 0;
        tmp = tmp->next;
    }
}

bool enqueue(t_room *prevRoom, t_list **queue) {
    t_list  *neigh = prevRoom->neigh;
    t_room  *roomTmp = NULL;
    while (neigh) {
        roomTmp = (t_room *)neigh->content;
        if (roomTmp->isEnd == true) {
            roomTmp->isInqueue = true;
            ft_lstadd_front(queue, ft_lstnew_prev(roomTmp, *queue));
            return true;
        } else if (roomTmp->isSeen == NOT_SEEN && roomTmp->isInqueue == false) {
            roomTmp->isInqueue = true;
            ft_lstadd_back(queue, ft_lstnew_prev(roomTmp, *queue));
        }
        neigh = neigh->next;
    }
    return false;
}

t_path  *createPath(t_list **queue, t_room *start){
    t_path  *ret = getEmptyPath();
    t_list  *tmp = *queue;
    t_room  *roomTmp = NULL;
    while (tmp) {
        roomTmp = (t_room *)tmp->content;
        if (isMultiNode(roomTmp) && roomTmp->isEnd == false && roomTmp->isStart == false) {
            roomTmp->usedInPath++;
            ft_lstadd_back(&(ret->multiRoom), ft_lstnew(roomTmp));
        }
        ft_lstadd_front(&(ret->roomList), ft_lstnew(roomTmp));
        tmp = tmp->prev;
    }
    roomTmp = (t_room *)ret->roomList->content;
    if (!roomTmp->isStart)
        ft_lstadd_front(&(ret->roomList), ft_lstnew(start));
    ret->pathSize = ft_lstsize(ret->roomList);
    ret->antsInPath = 0;
    ret->ants = NULL;
    ret->full = false;
    ret->color = NULL;
    return ret;
}

t_list *pathFinding(t_simulation *simu, t_room *start) {
    t_list *queue = NULL;
    t_room *current = NULL;
    t_list *poped = NULL;
    t_list *paths = NULL;

    start->isSeen = true;
    ft_lstadd_back(&queue, ft_lstnew(start));
    while (ft_lstsize(queue) > 0) {
        current = (t_room *)queue->content;
        current->isSeen = SEEN;
        if (current->isEnd == true || enqueue(current, &queue) == true) {
            ft_lstadd_back(&paths, ft_lstnew(createPath(&queue, simu->graph->startRoom)));
            custom_pop(&queue, &poped);
        }
        custom_pop(&queue, &poped);
    }
    resetGraph(&simu);
    ft_lstclear(&queue, noFree);
    ft_lstclear(&poped, noFree);
    return paths;
}