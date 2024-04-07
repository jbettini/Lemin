#include "lemIn.h"

bool    isAugmentedPath(t_path *p, t_list *paths) {
    t_list  *tmp = paths;
    t_room  *r  = NULL;
    t_room  *r2  = NULL;
    while (p->problematicRoom) {
        r = p->problematicRoom->content;
        tmp = paths;
        while (tmp) {
            r2 = tmp->content;
            if (ft_strequ(r->name, r2->name))
                return false;
            tmp = tmp->next;
        }
        p->problematicRoom = p->problematicRoom->next;
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

void    createSolution(t_simulation *simu) {
    
    ft_lstadd_back(&simu->fasterPath, ft_lstnew(pathFinding(simu, simu->graph->startRoom)));
    initProblematicNodes(&(simu->fasterPath));
    if (simu->ants <= 0 || ft_lstsize(simu->fasterPath) == 0)
        handleErrorWithoutStr(dataEnoughError);
    
    simu->bestPath = simu->fasterPath->content;
    // simu->fasterPath = findAugmentedPath(faster);
}