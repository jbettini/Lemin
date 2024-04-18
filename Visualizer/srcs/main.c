/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 01:16:22 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/18 23:05:10 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

t_visu v;

int main(int ac, char**av) {
    (void)av;
    (void)ac;
    
    setRandomizer();
    signal(SIGINT, handle_sigint);
    if ((SDL_Init(SDL_INIT_VIDEO)) != 0)
        error_sdl("Init sdl failed");
    else {
        initVisu(&v);

        
        t_simulation	*simu = parseStdin(true);
        if (isIncompleteSimulation(simu))
            handleErrorWithoutStr(dataEnoughError);
        v.vcolors = simu->vColors;
        createSolution(simu);
        assignColor(simu->bestPath);
        handleAnts(simu->bestPath, simu);
        drawGraph(simu, simu->graph->startRoom->posX, simu->graph->startRoom->posY, &v);
        while (v.run) {
            if (SDL_PollEvent(&v.event)) {
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
                            case SDLK_SPACE:
                                v.stop = !v.stop;
                                break;
                            case SDLK_w:
                                if (v.antSpeed <= 0.04)
                                    v.antSpeed += 0.001;
                                break;
                            case SDLK_s:
                                if (v.antSpeed > 0.001)
                                    v.antSpeed -= 0.001;
                                break;
                        }
                        break;
                }
            }
            drawGraph(simu, simu->graph->startRoom->posX, simu->graph->startRoom->posY, &v);
            SDL_Delay(10);
        }
        cleanSimulation(simu);
        SDL_DestroyRenderer(v.render);
        SDL_DestroyWindow(v.w);
        SDL_Quit();
    }
    return (0);
}