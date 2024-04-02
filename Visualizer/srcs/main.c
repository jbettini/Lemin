/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 01:16:22 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/02 04:05:35 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

t_visu v;

void handle_sigint(int sig) {
    printf("singint detected : %d\n", sig);
    SDL_DestroyRenderer(v.render);
    SDL_DestroyWindow(v.w);
    SDL_Quit();
    // sleep(5);
    exit(0); 
}

void    error_sdl(char *str) {
    SDL_Log("error: %s: %s\n", str, SDL_GetError());
    SDL_Quit();
    exit(1);
}

void    resetSeen(t_simulation **simu){
    t_graph *g = (*simu)->graph;
    t_list  *tmp = g->rooms;
    t_room  *r = NULL;

    while (tmp) {
        r = (t_room *)tmp->content;
        r->isSeen = 0;
        tmp = tmp->next;
    }
}

void drawThickLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
    for (int i = 0 ; i <= 4; i++) {
        SDL_RenderDrawLine(renderer, x1 + i, y1, x2 + i, y2);
        SDL_RenderDrawLine(renderer, x1, y1 + i, x2, y2 + i);
    }
}

void drawFilledCircle(SDL_Renderer *renderer, int centerX, int centerY, float radius, int color) {
    if (color == 1)
        SDL_SetRenderDrawColor(renderer, 126, 28, 41, 255);
    else if (color == 2)
        SDL_SetRenderDrawColor(renderer, 29, 109, 63, 255);
    else
        SDL_SetRenderDrawColor(renderer, 122, 122, 122, 255);
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius)
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        }
    }
}

void    initPos(int x, int y, t_pos *pos) {
    pos->x = x;
    pos->y = y;
}

void    initFPos(int x, int y, t_fpos *pos) {
    pos->x = x;
    pos->y = y;
}


void    initVisu(t_visu *v) {
    v->w = SDL_CreateWindow("Visu-hex", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);
    if (!v->w)
        error_sdl("CreateWindow failed");
    v->render = SDL_CreateRenderer(v->w, -1, SDL_RENDERER_SOFTWARE);
    if (!v->render)
        error_sdl("CreateRenderer failed");
    v->run = true;
    v->firstDraw = false;
    
    v->zoom.zoom = false;
    v->zoom.dezoom = false;
    v->zoom.Factor = 60.0;
    
    initPos(0, 0,&(v->mouse));
    initPos(0, 0,&(v->offset));
}

// void drawGraph(t_list *roomList, int centerX, int centerY, t_visu *v) {
//     if (v->firstDraw == false) {
//         initPos((W / 2) - (int)(centerX * v->zoom.Factor),\
//                     (H / 2) - (int)(centerY * v->zoom.Factor),&(v->offset));
//         v->firstDraw = true;
//     }
//     else if (v->zoom.zoom || v->zoom.dezoom){
//         float preZoomX = (v->mouse.x - v->offset.x) / v->zoom.Factor;
//         float preZoomY = (v->mouse.y - v->offset.y) / v->zoom.Factor;
//         if (v->zoom.zoom)
//             v->zoom.Factor *= 1.1;
//         else
//             v->zoom.Factor *= 0.9;
//         float postZoomX = (v->mouse.x - v->offset.x) / v->zoom.Factor;
//         float postZoomY = (v->mouse.y - v->offset.y) / v->zoom.Factor;
//         v->offset.x += (postZoomX - preZoomX) * v->zoom.Factor;
//         v->offset.y += (postZoomY - preZoomY) * v->zoom.Factor;
//         v->zoom.zoom = false;
//         v->zoom.dezoom = false;
//     }
//     t_list  *tmp = roomList;
//     SDL_SetRenderDrawColor(v->render, 0, 0, 0, 255);
//     SDL_RenderClear(v->render);
//     SDL_SetRenderDrawColor(v->render, 200, 200, 200, 255);
//     while (roomList) {
//         t_room *currentRoom = (t_room *)roomList->content;
//         t_list *neighbors = currentRoom->neigh;
//         while (neighbors) {
//             t_room *neighRoom = (t_room *)neighbors->content;
//             int startX = (int)(currentRoom->posX * v->zoom.Factor) + v->offset.x;
//             int startY = (int)(currentRoom->posY * v->zoom.Factor) + v->offset.y;
//             int endX = (int)(neighRoom->posX * v->zoom.Factor) + v->offset.x;
//             int endY = (int)(neighRoom->posY * v->zoom.Factor) + v->offset.y;
//             if ((startX >= 0 && startX <= W && startY >= 0 && startY <= H) || \
//                             (endX >= 0 && endX <= W && endY >= 0 && endY <= H)) {
//                 drawThickLine(v->render, startX, startY, endX, endY);
//             }
//             neighbors = neighbors->next;
//         }
//         roomList = roomList->next;
//     }


//     if (v->zoom.Factor > 30) {
//         while (tmp) {
//             t_room *currentRoom = (t_room *)tmp->content;
//             int circleX = (int)(currentRoom->posX * v->zoom.Factor) + v->offset.x;
//             int circleY = (int)(currentRoom->posY * v->zoom.Factor) + v->offset.y;
//             if (circleX >= -0.3 * v->zoom.Factor && circleX <= W + 0.3 * v->zoom.Factor && \
//                         circleY >= -0.3 * v->zoom.Factor && circleY <= H + 0.3 * v->zoom.Factor) {
//                 int color = 0;
//                 if (currentRoom->isStart)
//                     color = 1;
//                 else if (currentRoom->isEnd)
//                     color = 2;
//                 drawFilledCircle(v->render, circleX, circleY, 0.3 * v->zoom.Factor, color);
//             }

//             tmp = tmp->next;
//         }
//     }
//     SDL_RenderPresent(v->render);
// }

void drawGraph(t_list *roomList, int centerX, int centerY, t_visu *v) {
    if (v->firstDraw == false) {
        v->offset.x = (W / 2) - (int)(centerX * v->zoom.Factor);
        v->offset.y = (H / 2) - (int)(centerY * v->zoom.Factor);
        v->firstDraw = true;
    }
    else if (v->zoom.zoom || v->zoom.dezoom){
        float preZoomX = (v->mouse.x - v->offset.x) / v->zoom.Factor;
        float preZoomY = (v->mouse.y - v->offset.y) / v->zoom.Factor;
        if (v->zoom.zoom)
            v->zoom.Factor *= 1.1;
        else
            v->zoom.Factor *= 0.9;
        float postZoomX = (v->mouse.x - v->offset.x) / v->zoom.Factor;
        float postZoomY = (v->mouse.y - v->offset.y) / v->zoom.Factor;
        v->offset.x += (postZoomX - preZoomX) * v->zoom.Factor;
        v->offset.y += (postZoomY - preZoomY) * v->zoom.Factor;
        v->zoom.zoom = false;
        v->zoom.dezoom = false;
    }



    
    t_list  *tmp = roomList;
    SDL_SetRenderDrawColor(v->render, 0, 0, 0, 255);
    SDL_RenderClear(v->render);
    SDL_SetRenderDrawColor(v->render, 200, 200, 200, 255);
    while (roomList) {
        t_room *currentRoom = (t_room *)roomList->content;
        t_list *neighbors = currentRoom->neigh;
        while (neighbors) {
            t_room *neighRoom = (t_room *)neighbors->content;
            drawThickLine(v->render,(int)(currentRoom->posX * v->zoom.Factor) + v->offset.x, 
                                    (int)(currentRoom->posY * v->zoom.Factor) + v->offset.y, 
                                    (int)(neighRoom->posX * v->zoom.Factor) + v->offset.x, 
                                    (int)(neighRoom->posY * v->zoom.Factor) + v->offset.y);

            neighbors = neighbors->next;
        }
        roomList = roomList->next;
    }




    
    if (v->zoom.Factor > 30) {
        while (tmp) {
            t_room *currentRoom = (t_room *)tmp->content;
            int color = 0;
            if (currentRoom->isStart)
                color = 1;
            else if (currentRoom->isEnd)
                color = 2;
            drawFilledCircle(v->render, (currentRoom->posX * v->zoom.Factor) + v->offset.x,(currentRoom->posY * v->zoom.Factor) + v->offset.y, 0.3 * v->zoom.Factor, color);
            tmp = tmp->next;
        }
    }
    SDL_RenderPresent(v->render);
}



int main(int ac, char**av) {
    (void)av;
    (void)ac;
    
    signal(SIGINT, handle_sigint);
    if ((SDL_Init(SDL_INIT_VIDEO)) != 0)
        error_sdl("Init sdl failed");
    else {
        initVisu(&v);
        t_simulation	*simu = parseStdin();
        if (!simu)
            return ERROR;
        
        drawGraph(simu->graph->rooms, simu->graph->startRoom->posX, simu->graph->startRoom->posY, &v);
        while (v.run) {
            if (SDL_WaitEvent(&(v.event)) != 0) {
                switch (v.event.type) {
                    case SDL_QUIT:
                        v.run = false;
                        break;
                    case SDL_MOUSEWHEEL:
                        SDL_GetMouseState(&v.mouse.x, &v.mouse.y);
                        if (v.event.wheel.y > 0) {
                            v.zoom.zoom = true;
                        }
                        else if (v.event.wheel.y < 0) {
                            v.zoom.dezoom = true;
                        }
                        break;
                    case SDL_KEYDOWN:
                        switch (v.event.key.keysym.sym) {
                            case SDLK_ESCAPE:
                                v.run = false;
                                break;
                            case SDLK_UP:
                                v.offset.y += 10;
                                break;
                            case SDLK_DOWN:
                                v.offset.y -= 10;
                                break;
                            case SDLK_LEFT:
                                v.offset.x += 10;
                                break;
                            case SDLK_RIGHT:
                                v.offset.x -= 10;
                                break;
                        }
                        break;
                }
            }
            drawGraph(simu->graph->rooms, simu->graph->startRoom->posX, simu->graph->startRoom->posY, &v);
        }

        SDL_DestroyRenderer(v.render);
        SDL_DestroyWindow(v.w);
        SDL_Quit();
    }
    return (0);
}