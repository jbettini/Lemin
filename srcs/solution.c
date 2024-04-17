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
            if (ft_strequ(r->name, name))
                return false;
            rList = rList->next;
        }
        paths = paths->next;
    }
    return true;
}

t_list  *fasterAugmentedPath(t_list *paths) {
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

t_path  *findBestHeuristic(t_list   *allPaths) {
    t_path  *ret = NULL;
    t_path  *tmp = NULL;
    while (allPaths) {
        tmp = allPaths->content;
        if (ret == NULL)
            ret = tmp;
        else if (tmp->heuristic > ret->heuristic)
            ret = tmp;
        else if (tmp->heuristic == ret->heuristic && tmp->pathSize < ret->pathSize)
            ret = tmp;
        allPaths = allPaths->next;
    }
    return ret;
}

bool    isUsedNode(t_room *r, t_path *p) {
    t_room  *r2 = NULL;
    t_list  *pbNodes = p->problematicRoom;
    while (pbNodes) {
        r2 = pbNodes->content;
        if (ft_strequ(r->name, r2->name))
            return true;
        pbNodes = pbNodes->next;
    }
    return false;
}

bool    isNotUsedPath (t_path *p, t_list *usedli) {
    if (p->unique)
        return false;
    t_list  *used = NULL;
    t_room  *s2 = NULL;
    t_path *tmp = NULL;
    t_room  *s1 = p->roomList->next->content;
    t_list  *pbNodes = p->problematicRoom;
    while (pbNodes) {
        used = usedli;
        while (used) {
            tmp = used->content;
            s2 = tmp->roomList->next->content;
            if (ft_strequ(s2->name, s1->name) || isUsedNode(pbNodes->content, used->content))
                return false;
            used = used->next;
        }
        pbNodes = pbNodes->next;
    }
    return true;
}

void    updatedUsedPaths(t_list **paths) {
    t_room  *r = NULL;
    t_path  *p = NULL;
    t_list  *rList = NULL;
    t_list  *ps = *paths;

    while (ps) {
        p = ps->content;
        rList = p->roomList;
        while(rList) {
            r = rList->content;
            if (!r->upUsed && r->usedInPath > 0) {
                r->upUsed = true;
                r->usedInPath--;
            }
            rList = rList->next;
        }
        ps = ps->next;
    }
    ps = *paths;
    while (ps) {
        p = ps->content;
        rList = p->roomList;
        while(rList) {
            r = rList->content;
            if (r->upUsed)
                r->upUsed = false;
            rList = rList->next;
        }
        ps = ps->next;
    }
}

t_list      *deleteUsedPath(t_list *allPaths, t_list *used) { 
    t_list  *ret = NULL;
    t_list  *paths = NULL;
    t_list  *pathsToUp = NULL;
    while (allPaths) {
        paths = allPaths->content;
        while (paths) {
            if (isNotUsedPath(paths->content, used))
                ft_lstadd_back(&ret, ft_lstnew(paths->content));
            else
                ft_lstadd_back(&pathsToUp, ft_lstnew(paths->content));
            paths = paths->next;
        }
        allPaths = allPaths->next;
    }
    updatedUsedPaths(&pathsToUp);
    ft_lstclear(&pathsToUp, noFree);
    return ret;
}

t_list  *getAllUniquePaths(t_list   *allPaths) {
    t_list  *ret = NULL;
    t_path  *p = NULL;
    t_list  *paths = NULL;
    while (allPaths) {
        paths = allPaths->content;
        while (paths) {
            p = paths->content;
            if (p->unique)
                ft_lstadd_back(&ret, ft_lstnew(p));
            paths = paths->next;
        }
        allPaths = allPaths->next;
    }
    return ret;
}

void    clearPathsHData(t_list **paths) {
    t_path  *p = NULL;
    t_list  *tmp = *paths;
    while (tmp) {
        p = tmp->content;
        ft_lstclear(&p->problematicRoom, noFree);
        p->problematicRoom = NULL;
        p->numsOfPbRooms = 0;
        p->heuristic = 0;
        tmp = tmp->next;
    }
}

void    calculateHeuristic(t_list **rest) {
    int     pbNodes = 0;
    t_path  *p = NULL;
    t_room  *r = NULL;
    t_list  *rList = NULL;
    t_list  *tmp = *rest;

    clearPathsHData(rest);
    while (tmp) {
        p = tmp->content;
        rList = p->multiRoom;
        while(rList) {
            r = rList->content;
            if (r->usedInPath > 1) {
                pbNodes++;
                ft_lstadd_back(&p->problematicRoom, ft_lstnew(r));
            }
            rList = rList->next;
        }
        p->numsOfPbRooms = pbNodes;
        p->heuristic = 1 / (p->pathSize + (p->numsOfPbRooms * 1.5));
        if (pbNodes == 0)
            p->unique = true;
        pbNodes = 0;
        tmp = tmp->next;
    }
}

t_list            *createHPath(t_simulation *s){
    t_list  *ret = NULL;
    t_list  *rest = NULL;
    t_path  *used = NULL;
    t_list  *hPath = getAllUniquePaths(s->allPaths);
    do
    {
        if (rest)
            ft_lstclear(&rest, noFree);
        rest = deleteUsedPath(s->allPaths, hPath);
        if(rest) {
            calculateHeuristic(&rest);
            used = findBestHeuristic(rest);
            ft_lstadd_back(&hPath, ft_lstnew(used));
        }
    } while (rest);
    ret = sortS(hPath);
    ft_lstclear(&hPath, noFree);
    return ret;
}

void    createSolution(t_simulation *simu) {
    
    t_list  *allFaster = pathFinding(simu, simu->graph->startRoom);
    if (allFaster) {
        ft_lstadd_back(&simu->fasterPath, ft_lstnew(allFaster));
        initProblematicNodes(&(simu->fasterPath));
    } else if (simu->ants <= 0 || ft_lstsize(simu->fasterPath) == 0)
        handleErrorWithoutStr(dataEnoughError);
    t_list  *faster = fasterAugmentedPath(simu->fasterPath->content);
    t_list *tmp = simu->graph->startRoom->neigh;
    while (tmp) {
        simu->graph->startRoom->isSeen = SEEN;
        ft_lstadd_back(&simu->allPaths, ft_lstnew(pathFinding(simu, tmp->content)));
        tmp = tmp->next;
    }
    resetEverything(simu);
    subsetsMultiRoom(&(simu->allPaths));
    initProblematicNodes(&(simu->allPaths));
    t_list  *flow = createHPath(simu);
    simu->bestPath = flow;
    // printf("faster %d : flow %d\n", ft_lstsize(faster), ft_lstsize(flow));
    if (ft_lstsize(faster) >= ft_lstsize(flow) || simu->ants <= ft_lstsize(faster)) {
        simu->bestPath = faster;
        ft_lstclear(&flow, noFree);
    } else
        ft_lstclear(&faster, noFree);
}