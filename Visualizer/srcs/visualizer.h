/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:22:29 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/02 03:48:25 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
    #define VISUALIZER_H

#include "../../libft/libft.h"
#include "../../srcs/lemIn.h"
#include <SDL2/SDL.h>


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
    SDL_Renderer    *render;
    SDL_Window      *w;
    SDL_Event       event;
    bool            run;
    bool            firstDraw;
    t_zoom          zoom;
    t_pos           mouse;
    t_pos           offset;
}               t_visu;




void    error_sdl(char *str);

#endif