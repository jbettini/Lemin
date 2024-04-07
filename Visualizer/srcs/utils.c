#include "visualizer.h"

void handle_sigint(int sig) {
    printf("singint detected : %d\n", sig);
    SDL_DestroyRenderer(v.render);
    SDL_DestroyWindow(v.w);
    SDL_Quit();
    // sleep(5);
    // clean all
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

void drawFilledCircle(SDL_Renderer *renderer, int centerX, int centerY, float radius, t_color color) {

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
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
    v->stop = false;
    v->firstDraw = false;

    v->readyToEnqueue = true;
    
    v->antSpeed = 0.015;
    v->zoom.zoom = false;
    v->zoom.dezoom = false;
    v->zoom.Factor = 60.0;
    v->queue = NULL;
    
    initPos(0, 0,&(v->mouse));
    initPos(0, 0,&(v->offset));
}

void    assignColor(t_list *paths){
    t_path *tmp;
    while (paths) {
        tmp = paths->content;
        tmp->color = getRandomColor();
        paths = paths->next;
    }
}
