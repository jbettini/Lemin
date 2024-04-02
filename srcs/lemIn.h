/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemIn.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:22:29 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/02 03:22:32 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN
    #define LEM_IN

#include "../libft/libft.h"

typedef struct  s_room
{
	t_list  *neigh;
    int     numOfNeigh;
    int     posX, posY;
    bool    isStart, isEnd;
    char    *name;
    int     isSeen;
    bool    isInqueue;
    int     usedInPath;
    int     neighSize;
    int     inPath;
}				t_room;

typedef struct  s_graph
{
    t_list  *rooms;
    t_room  *startRoom;
    t_room  *endRoom;
    int     numRooms;
    
}               t_graph;

typedef struct  s_simulation
{
    t_graph *graph;
    int     ants;
    t_list  *roomsNames;
    t_list  *paths;
}               t_simulation;

// typedef struct  s_paths
// {
//     	t_list  *roomList;
//     	t_list  *multiRoom;
//     	t_list  *problematicRoom;
//     	bool    unique;
//		int		pathSize;
//		int		heuristic;
// }               t_paths;

// typedef struct  s_ant
// {
//     	t_list  *path;
//		t_room	*currentRoom;
// }               t_ant;



# define NOT_SEEN   0
# define SEEN       1


// clean.c

void cleanRoom();
void cleanGraph();
void cleanSimulation();
void safeFree(void *ptr);
void freeTab(char **tab);

// //error.c
int invalidNumOfArg(void);
int fatalError(void);
int badInputFile(char *badLine);
int badInstruction(char *badLine);
int badRoomSettings(char *badLine);
int badLinkSettings(char *badLine);
int linkAlreadyExists(char *badLine);
void handleErrorWithoutStr(int (*fun)(void));
void handleErrorWithStr(char *line, int (*fun)(char *));

// init.c
t_graph *getEmptyGraph(void);
t_simulation *getEmptySimulation(void);
t_room *roomCopy(t_room *src);
t_room *roomConstructor(char *str);

// //parse.c
void handleLink(char *str, t_simulation **simu);
t_simulation *parseStdin();

// // algo
void custom_pop(t_list **list, t_list **poped);
bool enqueue(t_room *prevRoom, t_list **queue);
char **createPath(t_list *queue);
void resetGraph(t_simulation **s);
bool pathFinding(t_simulation *simu, t_room *start);

// // print.c
void printQueue(t_list *queue);
void printRQueue(t_list *queue);
void colorPrint(char *color, char *str);
void printDataStr(char *prefix, char *data);
void printDataInt(char *prefix, int data);
void printNeighbors(t_list *n);
void printRoom(t_room *room);
void printGraph(t_graph *g);
void printSimu(t_simulation *simu);

// // utils
char *ft_strdup_except(char *src, char exclude);
int numOfOccurences(const char *str, char c);
bool onlyDigitStr(char *str);
bool isComment(char *str);
bool isStart(char *str);
bool isEnd(char *str);
bool isRoom(char *str);
bool isLink(char *str);
bool isInstruction(char *str);
bool isNullOrEmpty(char *str);
bool nameExist(char *str, t_list *allName);
bool nameIsValid(char *str, t_list *allName);
bool posIsValid(t_room *r, t_list *allRooms);
t_room *getRoomWithName(char *str, t_list **rooms);
bool lstStrEqu(t_list *lst, char *str);
t_room *Cast(t_list *roomNode);

#endif