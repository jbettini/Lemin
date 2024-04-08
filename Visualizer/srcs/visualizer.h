/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:22:29 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/08 12:58:37 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
    #define VISUALIZER_H

#include "../../libft/libft.h"
#include "../../srcs/lemIn.h"
#include <SDL2/SDL.h>
#include <math.h>

#define H 800
#define W 1200


typedef struct s_pos {
    int x, y;
}               t_pos;

typedef struct s_fpos {
    float x, y;
}               t_fpos;


typedef struct s_zoom {
    bool    zoomUsed;
    bool    zoom, dezoom;
    float   Factor;
}               t_zoom;

typedef struct  s_visu
{
    float           antSpeed;
    int             antsReached;
    SDL_Renderer    *render;
    SDL_Window      *w;
    SDL_Event       event;
    bool            stop;
    bool            run;
    bool            firstDraw;
    bool            readyToEnqueue;
    t_zoom          zoom;
    t_pos           mouse;
    t_pos           offset;
    t_list          *queue;
}               t_visu;


t_visu v;

void handle_sigint(int sig);
void error_sdl(char *str);
void resetSeen(t_simulation **simu);
void drawThickLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
void drawFilledCircle(SDL_Renderer *renderer, int centerX, int centerY, float radius, t_color color);
void initPos(int x, int y, t_pos *pos);
void initFPos(int x, int y, t_fpos *pos);
void initVisu(t_visu *v);
void drawGraph(t_simulation *simu, int centerX, int centerY, t_visu *v);
void assignColor(t_list *paths);
bool drawMove(t_ant **ant);
void handleAntsPosition(t_list *ants, t_visu *v);
void assignPathColor(t_list *paths); 
bool isIncompleteSimulation(t_simulation *simu);
float distance(int x1, int y1, int x2, int y2);
bool updateAntPosition(t_ant *ant);
bool updatePos(t_ant **ant);
void resetLoop(t_visu *v);
t_color getGreyColor();
t_color getGreenColor();
t_color getRedColor();
t_color getBlueColor();


t_simulation *parseStdin(void);


#endif