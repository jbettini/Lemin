/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 01:16:22 by jbettini          #+#    #+#             */
/*   Updated: 2024/03/31 11:18:23 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"



void    error_sdl(char *str) {
    SDL_Log("error: %s: %s\n", str, SDL_GetError());
    SDL_Quit();
    exit(1);
}


int main(int ac, char**av) {
    (void)av;
    (void)ac;
    bool    running = true;
    
    if ((SDL_Init(SDL_INIT_VIDEO)) != 0)
        error_sdl("Init sdl failed");
    else {
        SDL_Window *w = SDL_CreateWindow("Visu-hex", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);
        if (!w)
            error_sdl("CreateWindow failed");
        SDL_Renderer *render = SDL_CreateRenderer(w, -1, SDL_RENDERER_SOFTWARE);
        if (!render)
            error_sdl("CreateRenderer failed");
        // ------------------------------------
        t_simulation	*simu = parseStdin();
        if (!simu)
            return ERROR;


        if (SDL_SetRenderDrawColor(render, 255, 255, 255, 255) != 0)
            error_sdl("color draw failed");
        if (SDL_RenderDrawLine(render,  50, 50, 500, 500) != 0)
            error_sdl("line draw failed");

        SDL_Event event;
        SDL_RenderPresent(render);

        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                }
            }    
        }

        // ------------------------------------


        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(w);
        SDL_Quit();
    }
    
    return (0);
}