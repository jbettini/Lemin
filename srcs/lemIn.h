/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemIn.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:22:29 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/16 20:31:23 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN
    #define LEM_IN

#include "../libft/libft.h"

typedef struct  s_room
{
	t_list  *neigh;
    int     posX, posY;
    bool    isStart, isEnd;
    char    *name;
    int     isSeen;
    bool    isInqueue;
    bool    upUsed;
    
    int     usedInPath;         // need an update maybe
    int     neighSize;
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
    bool    visu;
    t_list  *roomsNames;
    t_list  *allPaths;
    t_list  *fasterPath;
    t_list  *bestPath;
    t_list  *antsQueue;
}               t_simulation;

typedef struct  s_path
{
    	t_list  *roomList;
    	t_list  *multiRoom;
    	t_list  *problematicRoom;
		int		pathSize;
    	bool    unique;
        int     numsOfPbRooms;

    // distribution
        int     antsInPath;
        t_list  *ants;
        bool    full;
        bool    sorted;
        t_color *color;
        
    
    // heuristic
		float		heuristic;
        float       totalWeigh;
}               t_path;

typedef struct  s_ant
{
        int     num;
        float   posX, posY;
        float   distX, distY;
        bool    reached;
        bool    moved;
        bool    inQueue;
        bool    ended;
        t_list  *roomList;
        t_path  *path;
        t_color *color;
}               t_ant;

# define NOT_SEEN   0
# define SEEN       1

//solution.c
void    createSolution(t_simulation *simu);
t_list  *findAugmentedPath(t_list *paths);
bool    isAugmentedPath(t_path *p, t_list *paths);

// distribution.c
void    simplePop(t_list **list);
int     getNextHigherSize(t_list *p, int size);
t_ant   *getAnt(int currentAnt, t_path **p);
void    fill(t_list *paths, int totalAnts, int currentAnt, t_simulation *s);
void    handleAnts(t_list *paths, t_simulation *s);
void    printMove(t_ant *ant);
void    resetForLoop(t_list *queue);
void    headToBack(t_list **list);
bool    moveForward(t_ant **ant);
void    antsMoving(t_list *ants);
t_list  *setQueueAnts(t_list *paths);


// clean.c

void    cleanSimulation(t_simulation *simulation);
void    safeFree(void *ptr);
void    freeTab(char **tab);

// //error.c
int     invalidNumOfArg(void);
int     fatalError(void);
int     badInputFile(char *badLine);
int     badInstruction(char *badLine);
int     badRoomSettings(char *badLine);
int     badLinkSettings(char *badLine);
int     linkAlreadyExists(char *badLine);
void    handleErrorWithoutStr(int (*fun)(void));
void    handleErrorWithStr(char *line, int (*fun)(char *));
int     dataEnoughError(void);

// init.c
t_graph         *getEmptyGraph(void);
t_simulation    *getEmptySimulation(void);
t_room          *roomCopy(t_room *src);
t_room          *roomConstructor(char *str);
t_path          *getEmptyPath(void);
void            initProblematicNodes(t_list **allPaths);

// //parse.c
void            handleLink(char *str, t_simulation **simu);
t_simulation    *parseStdin();

// pathsCreate.c
t_path  *createPath(t_list **queue, t_room *start);

// path_finding.c
void    custom_pop(t_list **list, t_list **poped);
bool    enqueue(t_room *prevRoom, t_list **queue);
void    resetGraph(t_simulation **s);
t_list  *pathFinding(t_simulation *simu, t_room *start);

// // print.c
void    printQueue(t_list *queue);
void    printRQueue(t_list *queue);
void    colorPrint(char *color, char *str);
void    printDataStr(char *prefix, char *data);
void    printDataInt(char *prefix, int data);
void    printNeighbors(t_list *n);
void    printRoom(t_room *room);
void    printGraph(t_graph *g);
void    printSimu(t_simulation *simu);
void	printPath(t_path *path);
void	printPaths(t_list	*paths);
void	printAllPaths(t_list	*allPaths);
void	printRooms(t_list *r);
void	printMultiNodes(t_graph *g);
void	printRoomsName(t_list	*n, char *str);
void	printAntsInPath(t_list	*paths);
void    printAntsInList(t_list  *ants);
void	printAnt(t_ant *a);
void	printDataFloat(char *prefix, float data);
void	printSpecificRoom(t_graph *g, char *n);

// // utils
t_room  *getRoomWithName(char *str, t_list **rooms);
t_room  *Cast(t_list *roomNode);
char    *ft_strdup_except(char *src, char exclude);
int     numOfOccurences(const char *str, char c);
bool    onlyDigitStr(char *str);
bool    isComment(char *str);
bool    isStart(char *str);
bool    isEnd(char *str);
bool    isRoom(char *str);
bool    isLink(char *str);
bool    isInstruction(char *str);
bool    isNullOrEmpty(char *str);
bool    nameExist(char *str, t_list *allName);
bool    nameIsValid(t_room *r, t_list *allName);
bool    posIsValid(t_room *r, t_list *allRooms);
bool    lstStrEqu(t_list *lst, char *str);
bool    isMultiNode(t_room *r);
bool    isProblematicNode(t_room *r);
bool    isPositiveNumber(char *str);
bool    isValidNum(char *str);
bool    isIncompleteSimulation(t_simulation *simu);

#endif