/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:44:47 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/07 22:59:35 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemIn.h"

void    printQueue(t_list *queue) {
    printf("=============QUEUE===========\nSize of queue : %d\n", ft_lstsize(queue));
    t_room  *prevRoom = NULL;
    while (queue) {
        if (queue->prev) {
            prevRoom = (t_room *)queue->prev->content;
            printDataStr("Previous room : ", prevRoom->name);
        } else printDataStr("Previous room : ", "NULL");

        printRoom(queue->content);

        queue = queue->next;
    }
    printf("=============================\n");
}

void    printRQueue(t_list *queue) {
    printf("============= REVERSE QUEUE===========\nSize of queue : %d\n", ft_lstsize(queue));
    t_room  *prevRoom = NULL;
    while (queue) {
        if (queue->prev) {
            prevRoom = (t_room *)queue->prev->content;
            printDataStr("Previous room : ", prevRoom->name);
        } else printDataStr("Previous room : ", "NULL");

        printRoom(queue->content);

        queue = queue->prev;
    }
    printf("=============================\n");
}

void	printPath(t_path *path) {
	colorPrint(TXT_RED, "\n-------------------------------\n");
	printDataStr("Unique : ", path->unique ? "true" : "false");
	printDataInt("Path Size : ", path->pathSize);
	colorPrint(TXT_YELLOW, "Rooms :\n");
	printRoomsName(path->multiRoom, "Multi Room : ");
	printRoomsName(path->problematicRoom, "Problematic Room : ");
	t_list	*tmp = path->roomList;
	while (tmp) {
		printRoom(tmp->content);
		tmp = tmp->next;
	}
	colorPrint(TXT_RED, "\n-------------------------------\n");
}


void    printAntsInList(t_list  *ants) {
	t_ant	*a;
	
	while (ants) {
			a = ants->content;
			printAnt(a);
			ants = ants->next;
		}
}

void	printAnt(t_ant *a) {
	printDataInt("ant number :", a->num);
	printRoomsName(a->roomList, "path used : ");
	printDataFloat("ant posX:", a->posX);
	printDataFloat("ant posY:", a->posY);
	printDataStr("Reached: ", a->reached ? "true" : "false");
	ft_putendl("");
}



void	printAntsInPath(t_list	*paths) {
	t_list	*tmp;
	t_path 	*path;
	t_ant	*a;
	while (paths) {
		path = paths->content;
		tmp = path->ants;
		while (tmp) {
			a = tmp->content;
			printAnt(a);
			tmp = tmp->next;
		}
		paths = paths->next;
	}
}

void	printPaths(t_list	*paths) {
	colorPrint(TXT_MAGENTA, "\n---------\nPaths : \n");
	while (paths) {
		printPath(paths->content);
		paths = paths->next;
	}
	colorPrint(TXT_MAGENTA, "\n--------------------\n");
}

void	printAllPaths(t_list	*allPaths) {
	colorPrint(TXT_MAGENTA, "\n---------\nALL Paths : \n");
	int i = 1;
	while (allPaths) {
		printDataInt("Node number : ", i++);
		printPaths(allPaths->content);
		allPaths = allPaths->next;
	}
	colorPrint(TXT_MAGENTA, "\n--------------------\n");
}

void	colorPrint(char *color, char *str){
	printf("%s%s%s", color, str, FANCY_RESET);
}

void	printDataStr(char *prefix, char *data){
	colorPrint(TXT_YELLOW, prefix);
	colorPrint(TXT_BLUE, data);
	printf("\n");
}

void	printDataInt(char *prefix, int data){
	colorPrint(TXT_YELLOW, prefix);
	printf("%s%d%s", TXT_BLUE, data, FANCY_RESET);
	printf("\n");
}

void	printDataFloat(char *prefix, float data) {
	colorPrint(TXT_YELLOW, prefix);
	printf("%s%f%s", TXT_BLUE, data, FANCY_RESET);
	printf("\n");
}

void	printRoomsName(t_list	*n, char *str){
	colorPrint(TXT_YELLOW, str);
	t_room *tmp = NULL;
	while (n) {
		tmp = (t_room *)n->content;
		colorPrint(TXT_BLUE, tmp->name);
		printf(n->next ? " | ": "\n");
		n = n->next;
	}
}

void	printRoom(t_room *room) {
	colorPrint(TXT_MAGENTA, "\n---\nRoom : \n");
	printDataStr("Name : ", room->name);
	if (room->isStart)
		printDataStr("Start : ", "true");
	else
		printDataStr("Start : ", "false");
	if (room->isEnd)
		printDataStr("End : ", "true");
	else
		printDataStr("End : ", "false");
		
	printDataStr("IsSeen: ", room->isSeen ? "true" : "false");
	printDataStr("IsInQueue: ", room->isInqueue ? "true" : "false");
	printDataInt("Used In Paths: ", room->usedInPath);
	colorPrint(TXT_YELLOW, "Position : ");
	printf("%s X = %d Y = %d%s\n", TXT_BLUE, room->posX, room->posY, FANCY_RESET);
	printDataInt("Number of Neighbors: ", room->neighSize);
	printRoomsName(room->neigh, "Neighbors : ");
	printf("\n");
}

void	printRooms(t_list *r) {
	colorPrint(TXT_MAGENTA, "\n-----\nRooms: \n");
	while (r) {
		printRoom(r->content);
		r = r->next;
	}
}

void	printGraph(t_graph *g) {
	colorPrint(TXT_MAGENTA, "\n-----\nGraph : \n");
	printDataInt("Number of Rooms : ", g->numRooms);
	t_list	*r = g->rooms;
	while (r) {
		printRoom(r->content);
		r = r->next;
	}
}

void	printMultiNodes(t_graph *g) {
	colorPrint(TXT_MAGENTA, "\n-----\nMulti Nodes : \n");
	t_list	*r = g->rooms;
	t_room	*rtmp = NULL;
	while (r) {
		rtmp = (t_room *)r->content;
		if (rtmp->neighSize > 2 && rtmp->isEnd == false && rtmp->isStart == false)
			printRoom(r->content);
		r = r->next;
	}
}


void	printSimu(t_simulation *simu) {
	colorPrint(TXT_MAGENTA, "Simulation\n----------\n\n");
	printDataInt("Number of Ants : ", simu->ants);
	// need to print all room name;
	t_list *tmp = simu->roomsNames;
	colorPrint(TXT_YELLOW, "ALL Rooms Names : ");
	while (tmp){
		colorPrint(TXT_BLUE ,tmp->content);
		printf(tmp->next ? " | ": "\n");
		tmp = tmp->next;
	}
	printGraph(simu->graph);
}
