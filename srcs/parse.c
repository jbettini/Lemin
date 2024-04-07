/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:17:50 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/06 10:42:38 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemIn.h"

void    handleLink(char *str, t_simulation **simu) {
    char    **args = ft_split(str, '-');
    t_simulation *s = *simu;
    if (!nameExist(args[0], s->roomsNames) || !nameExist(args[1], s->roomsNames)) {
        freeTab(args);
        handleErrorWithStr(str, badLinkSettings);
    }
    t_list  **rooms = &((*simu)->graph->rooms);
    t_room  *r1 = getRoomWithName(args[0], rooms);
    t_room  *r2 = getRoomWithName(args[1], rooms);
    if (r1 == NULL || r2 == NULL)
        handleErrorWithoutStr(fatalError);
    if (lstStrEqu(r1->neigh, r2->name) || lstStrEqu(r2->neigh, r1->name))
        handleErrorWithStr(str, linkAlreadyExists);
    ft_lstadd_back(&r1->neigh, ft_lstnew(r2));
    ft_lstadd_back(&r2->neigh, ft_lstnew(r1));
    r1->neighSize++;
    r2->neighSize++;
    freeTab(args);
}

t_simulation    *parseStdin() {
    t_simulation    *simu   = getEmptySimulation();
    char            *line;
    int             step = 0;

    while ((line = get_next_line(0))) {
        line = ft_strdup_except(line, '\n');
        ft_putendl(line);
        if (isNullOrEmpty(line))
            break ;
        if (isComment(line)) {   
            free(line);
            continue ;
        } else if (isPositiveNumber(line)) {
            if (step == 0) {
                simu->ants = ft_atoi(line);
                step = 1;
            }
            else
                handleErrorWithStr(line, badInputFile);               
        } else if (isInstruction(line)) {
            if (step == 1) {
                char *nextLine = get_next_line(0);
                t_room  *r = roomConstructor(nextLine);
                bool    validName = nameIsValid(r, simu->roomsNames);
                bool    validPos = posIsValid(r, simu->graph->rooms);
                if (validName == false || validPos == false) {
                    free(line);
                    free(r);
                    handleErrorWithStr(nextLine, badRoomSettings);
                } else {
                    if (isStart(line) && (!(simu->graph->startRoom))) {
                        r->isStart = true;  
                        simu->graph->startRoom = r; 
                    } else if (isEnd(line) && (!(simu->graph->endRoom))) {
                        r->isEnd = true;
                        simu->graph->endRoom = r;
                    } else {
                        free(nextLine);
                        handleErrorWithStr(line , badInstruction);
                    }
                    ft_lstadd_back(&simu->roomsNames, ft_lstnew(ft_strdup(r->name)));
                    ft_lstadd_back(&simu->graph->rooms, ft_lstnew(r));
                    simu->graph->numRooms++;
                    ft_putstr(nextLine);  
                    free(nextLine);
                }
            } else
                handleErrorWithStr(line, badInputFile);
        } 
        else if (isRoom(line)) {
            if (step == 1) {
                t_room *r = roomConstructor(line);
                bool    validName = nameIsValid(r, simu->roomsNames);
                bool    validPos = posIsValid(r, simu->graph->rooms);
                if (validName == false || validPos == false)
                    handleErrorWithStr(line, badRoomSettings);
                ft_lstadd_back(&simu->graph->rooms, ft_lstnew(r));
                ft_lstadd_back(&simu->roomsNames, ft_lstnew(ft_strdup(r->name)));
                simu->graph->numRooms++;
            } else
                handleErrorWithStr(line, badInputFile);
        } 
        else if (isLink(line)) {
            step = 2;
            handleLink(line, &simu);
        } 
        else {
            free(line);
            break ;
        }
        free(line);
    }
    ft_putendl("");
    return simu;
}