/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:44:47 by jbettini          #+#    #+#             */
/*   Updated: 2024/03/31 11:09:24 by jbettini         ###   ########.fr       */
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

void	printNeighbors(t_list	*n){
	colorPrint(TXT_YELLOW, "Neighbors : ");
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
	colorPrint(TXT_YELLOW, "isSeen : ");
	printf("%d\n", room->isSeen);
	colorPrint(TXT_YELLOW, "isInQueue : ");
	printf("%d\n", room->isInqueue);
	colorPrint(TXT_YELLOW, "Position : ");
	printf("%s X = %d Y = %d%s\n", TXT_BLUE, room->posX, room->posY, FANCY_RESET);
	printNeighbors(room->neigh);
	printf("\n");
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
