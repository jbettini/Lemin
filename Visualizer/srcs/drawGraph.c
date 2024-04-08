#include "visualizer.h"

void    handleZoom(int centerX, int centerY, t_visu *v) {
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
}

void    drawLink(t_list *roomList, t_visu *v) {
    SDL_SetRenderDrawColor(v->render, 0, 0, 0, 255);
    SDL_RenderClear(v->render);
    SDL_SetRenderDrawColor(v->render, 255, 255, 255, 255);
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
}

void    drawRooms(t_list *roomList, t_visu *v) {
    t_list  *tmp = roomList;
    
    if (v->zoom.Factor > 15) {
        while (tmp) {
            t_room *currentRoom = (t_room *)tmp->content;
            t_color color = getBlueColor();
            if (currentRoom->isStart)
                color = getRedColor();
            else if (currentRoom->isEnd)
                color = getGreenColor();
            drawFilledCircle(v->render, (currentRoom->posX * v->zoom.Factor) + v->offset.x, \
                                (currentRoom->posY * v->zoom.Factor) + v->offset.y, 0.3 * v->zoom.Factor, color);
            tmp = tmp->next;
        }
    }
}

void    drawAnts(t_list *queue, t_visu *v) {
    if (v->zoom.Factor > 20) {
        while (queue) {
            t_ant *currentAnt = (t_ant *)queue->content;
            drawFilledCircle(v->render, (currentAnt->posX * v->zoom.Factor) + v->offset.x, \
                                (currentAnt->posY * v->zoom.Factor) + v->offset.y, 0.15 * v->zoom.Factor, *(currentAnt->color));
            queue = queue->next;
        }
    }
}

void drawGraph(t_simulation *simu, int centerX, int centerY, t_visu *v) {
    printf("%lf", v->antSpeed);
    handleZoom(centerX, centerY, v);
    drawLink(simu->graph->rooms, v);
    handleAntsPosition(simu->antsQueue, v);
    drawAnts(v->queue, v);
    drawRooms(simu->graph->rooms, v);
    SDL_RenderPresent(v->render);
}