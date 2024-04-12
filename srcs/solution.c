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

bool    roomIsUsed(t_list *paths, char *name) {
    t_path *tmp = NULL;
    t_room  *r = NULL;
    t_list  *rList = NULL;
    while (paths) {
        tmp = paths->content;
        rList = tmp->roomList;
        while (rList) {
            r = rList->content;
            if (ft_strequ(r->name, name)) {
                printf("%s : %s\n", r->name, name);
                return false;
            }
            rList = rList->next;
        }
        paths = paths->next;
    }
    return true;
}

// bool    isAugmentedPath(t_path *p, t_list *paths) {

//     if (p->unique)
//         return true;
//     t_list  *rList = p->roomList;
//     t_room  *r = NULL;
//     while (rList) {
//         r = rList->content;
//         if (roomIsUsed(paths, r->name))
//             return false;
//         rList = rList->next;
//     }
//     return true;
// }

t_list  *findAugmentedPath(t_list *paths) {
    t_list *tmp = paths;
    t_list *ret = NULL;
    while (tmp) {
        if (isAugmentedPath(tmp->content, ret))
            ft_lstadd_back(&ret, ft_lstnew(tmp->content));
        tmp = tmp->next;
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
t_list  *sortS(t_list   *unsorted) {
    t_path  *p = NULL;
    t_list  *ret = NULL;
    t_list  *tmp = NULL;
    t_path  *ptmp = NULL;
    do
    {
        p = NULL;
        ptmp = NULL;
        tmp = unsorted;
        while (tmp) {
            ptmp = tmp->content;
            if (ptmp->sorted == false) {
                if (p == NULL)
                    p = ptmp;
                else if (p->pathSize > ptmp->pathSize)
                    p = ptmp;
            }
            tmp = tmp->next;
        }
        if (p) {
            p->sorted = true;
            ft_lstadd_back(&ret, ft_lstnew(p));
        }
    } while (p);
    return ret;
}

void    resetSorted(t_list **l) {
    t_list  *tmp = *l;
    t_path  *p = NULL;

    while (tmp) {
        p = tmp->content;
        p->sorted = false;
        tmp = tmp->next;
    }
}

t_list  *sortH(t_list   *unsorted) {
    t_path  *p = NULL;
    t_list  *ret = NULL;
    t_list  *tmp = NULL;
    t_path  *ptmp = NULL;
    do
    {
        p = NULL;
        ptmp = NULL;
        tmp = unsorted;
        while (tmp) {
            ptmp = tmp->content;
            if (ptmp->sorted == false) {
                if (p == NULL)
                    p = ptmp;
                else if (p->heuristic == ptmp->heuristic && p->pathSize > ptmp->pathSize)
                    p = ptmp;
                else if (p->heuristic < ptmp->heuristic)
                    p = ptmp;
            }
            tmp = tmp->next;
        }
        if (p) {
            p->sorted = true;
            ft_lstadd_back(&ret, ft_lstnew(p));
        }
    } while (p);
    resetSorted(&ret);
    return ret;
}

t_list            *createHPath(t_simulation *s){
    t_list  *paths = s->allPaths;
    t_list  *path = NULL;
    t_path  *tmp = NULL;
    t_path  *bestH = NULL;
    t_list  *unsorted = NULL;
    t_list  *sorted = NULL;
    t_list  *aPaths = NULL;
    t_list  *ret = NULL;
    while (paths) {
        if (paths->content == NULL || ft_lstsize(paths->content) <= 0) {
            paths = paths->next;
            continue;
        }
        path = (t_list *)paths->content;
        bestH = NULL;
        while (path) {
            tmp = (t_path *)path->content;
            if (tmp->unique) {
                bestH = tmp;
                break;
            }
            else if(bestH == NULL || bestH->heuristic < tmp->heuristic)
                bestH = tmp;
            path = path->next;
        }
        ft_lstadd_back(&unsorted, ft_lstnew(bestH));
        paths = paths->next;
    }
    sorted = sortH(unsorted);
    aPaths = findAugmentedPath(sorted);
    // printPaths(aPaths);
    // printSpecificRoom(s->graph, "Fuw2");
    // exit(0);
    ret = sortS(aPaths);
    ft_lstclear(&sorted, noFree);
    ft_lstclear(&unsorted, noFree);
    ft_lstclear(&aPaths, noFree);
    return ret;
}

void    createSolution(t_simulation *simu) {
    
    ft_lstadd_back(&simu->fasterPath, ft_lstnew(pathFinding(simu, simu->graph->startRoom)));
    initProblematicNodes(&(simu->fasterPath));
    if (simu->ants <= 0 || ft_lstsize(simu->fasterPath) == 0)
        handleErrorWithoutStr(dataEnoughError);
    t_list  *faster = findAugmentedPath(simu->fasterPath->content);
    t_list *tmp = simu->graph->startRoom->neigh;
    while (tmp) {
        simu->graph->startRoom->isSeen = SEEN;
        ft_lstadd_back(&simu->allPaths, ft_lstnew(pathFinding(simu, tmp->content)));
        tmp = tmp->next;
    }
    resetEverything(simu);
    subsetsMultiRoom(&(simu->allPaths));
    initProblematicNodes(&(simu->allPaths));
    // printPaths(faster);
    t_list  *flow = createHPath(simu);
    printPaths(flow);
    printPaths(faster);
    simu->bestPath = flow;
    // simu->bestPath = faster;
    ft_lstclear(&faster, noFree);
    if (ft_lstsize(faster) >= ft_lstsize(flow) || simu->ants <= ft_lstsize(faster)) {
        simu->bestPath = faster;
        ft_lstclear(&flow, noFree);
    } else
        ft_lstclear(&faster, noFree);
}