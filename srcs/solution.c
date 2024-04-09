#include "lemIn.h"

void    resetEverything(t_simulation *s) {
    t_list  *r = s->graph->rooms;
    t_room  *tmp = NULL;

    while (r) {
        tmp = r->content;
        tmp->usedInPath = 0;
        tmp->isInqueue = false;
        tmp->isSeen = NOT_SEEN;
        r = r->next;
    }
}

bool    isAugmentedPath(t_path *p, t_list *paths) {
    t_list  *tmp = paths;
    t_list  *pbRoom = p->problematicRoom;
    t_list  *pbRoom2 = NULL;
    t_path  *path = NULL;
    t_room  *r  = NULL;
    t_room  *r2  = NULL;
    while (pbRoom) {
        r = pbRoom->content;
        tmp = paths;
        while (tmp) {
            path = tmp->content;
            pbRoom2 = path->problematicRoom;
            while (pbRoom2) {
                r2 = pbRoom2->content;
                if (r2->isStart || r2->isEnd) {
                    pbRoom2 = pbRoom2->next;
                    continue ;
                }
                if (ft_strequ(r->name, r2->name))
                    return false;
                pbRoom2 = pbRoom2->next;
            }
            tmp = tmp->next;
        }
        pbRoom = pbRoom->next;
    }
    return true;
}

t_list  *findAugmentedPath(t_list *paths) {
    t_list *tmp = NULL;
    t_list *ret = NULL;
    while (paths) {
        tmp = paths->content;
        while (tmp) {
            if (isAugmentedPath(tmp->content, ret))
                ft_lstadd_back(&ret, ft_lstnew(tmp->content));
            tmp = tmp->next;
        }
        paths = paths->next;
    }
    return ret;
}

t_list  *getMultiRoom(t_list *rooms) {
    t_list  *ret = NULL;
    t_room  *r = NULL;
    while (rooms) {
        r = rooms->content;
        if (ft_lstsize(r->neigh) > 2)
            ft_lstadd_back(&ret, ft_lstnew(r));
        rooms = rooms->next;
    }
    return ret;
}

bool    isSameRoom(t_room *r1, t_room *r2) {
    if (ft_strequ(r1->name, r2->name))
        return true;
    return false;
}

void    updateUniqueMultiRoom(t_list *multiRooms, t_list **multiUnique) {
    bool    isPresent = false;
    t_list *unique = *multiUnique;
    while (multiRooms) {
        isPresent = false;
        while (unique) {
            if (isSameRoom(multiRooms->content, unique->content)) {
                isPresent = true;
                break ;
            }
            unique = unique->next;
        }
        if (isPresent == false)
            ft_lstadd_back(multiUnique, ft_lstnew(multiRooms->content));
        multiRooms = multiRooms->next;
    }
}

void    increaseMultiNode(t_list *l) {
    t_room *r = NULL;
    while (l) {
        r = l->content;
        r->usedInPath++;
        l = l->next;
    }
}

void    subsetsMultiRoom(t_list **allPaths) {
    t_list  *all = *allPaths;
    t_list  *subset = NULL;
    t_path  *path = NULL;
    t_list  *multiRoom = NULL;
    t_list  *uniqueMultiRoom = NULL;
    while (all) {
        subset = all->content;
        while (subset) {
            path = subset->content;
            multiRoom = getMultiRoom(path->roomList);
            updateUniqueMultiRoom(multiRoom, &uniqueMultiRoom);
            ft_lstclear(&multiRoom, noFree);
            subset = subset->next;
        }
        increaseMultiNode(uniqueMultiRoom);
        ft_lstclear(&uniqueMultiRoom, noFree);
        all = all->next;
    }
}

void    createSolution(t_simulation *simu) {
    
    ft_lstadd_back(&simu->fasterPath, ft_lstnew(pathFinding(simu, simu->graph->startRoom)));
    initProblematicNodes(&(simu->fasterPath));
    if (simu->ants <= 0 || ft_lstsize(simu->fasterPath) == 0)
        handleErrorWithoutStr(dataEnoughError);
    t_list  *faster = findAugmentedPath(simu->fasterPath);
    t_list *tmp = simu->graph->startRoom->neigh;
    while (tmp) {
        simu->graph->startRoom->isSeen = SEEN;
        ft_lstadd_back(&simu->allPaths, ft_lstnew(pathFinding(simu, tmp->content)));
        tmp = tmp->next;
    }
    resetEverything(simu);
    subsetsMultiRoom(&(simu->allPaths));
    initProblematicNodes(&(simu->allPaths));

    // calcul heuristic

    // sort avec un pointeur sur fonction qui est la fonction de comparéison

    // printf("\n=======================\n=======================\n");
    // printPaths(faster);
    // exit(0);
    
    // choose between fasteness and flow


    simu->bestPath = faster;
}