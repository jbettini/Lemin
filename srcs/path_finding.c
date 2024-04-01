#include "lemIn.h"

void custom_pop(t_list **list, t_list **poped) {
    if (*list == NULL)
        return;

    t_list *first = *list;
    *list = first->next;
    first->next = NULL;
    ft_lstadd_back(poped, first);
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

char    **createPath(t_list *queue){
    char    **ret = NULL;
    size_t  size = ft_lstsize_prev(queue);
    ret = malloc(sizeof(char *) * (size + 1));
    ret[size--] = NULL;
    t_room *tmp = NULL;
    while (queue) {
        tmp = (t_room *)queue->content;
        ret[size--] = ft_strdup(tmp->name);
        queue = queue->prev;
    }
    return ret;
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


bool pathFinding(t_simulation *simu, t_room *start) {
    t_list *queue = NULL;
    t_room *current = NULL;
    t_list *poped = NULL;
    bool    ret = false;

    start->isSeen = true;
    ft_lstadd_back(&queue, ft_lstnew(start));
    while (ft_lstsize(queue) > 0) {
        current = (t_room *)queue->content;
        current->isSeen = SEEN;
        if (current->isEnd == true || enqueue(current, &queue) == true) {
            ret = true;
            ft_lstadd_back(&simu->paths, ft_lstnew(createPath(queue))); // need a better backtracking fun to get overlapping nodes
            custom_pop(&queue, &poped);
        }
        custom_pop(&queue, &poped);
    }
    resetGraph(&simu);
    ft_lstclear(&queue, noFree);
    ft_lstclear(&poped, noFree);
    return ret;
}