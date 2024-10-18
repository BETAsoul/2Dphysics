#include "circles.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>


void drawCircle(int rad, SDL_Renderer *rndr, int centerX, int centerY){

    float p = 1.25 - rad;
    int x = 0;
    int y = rad;

    while(x<y){
        SDL_RenderDrawPoint(rndr, centerX + x, centerY + y);
        SDL_RenderDrawPoint(rndr, centerX + x, centerY - y);
        SDL_RenderDrawPoint(rndr, centerX - x, centerY + y);
        SDL_RenderDrawPoint(rndr, centerX - x, centerY - y);
        SDL_RenderDrawPoint(rndr, centerY + x, centerX + y);
        SDL_RenderDrawPoint(rndr, centerY + x, centerX - y);
        SDL_RenderDrawPoint(rndr, centerY - x, centerX + y);
        SDL_RenderDrawPoint(rndr, centerY - x, centerX - y);

        if(p<=0){
            x++;
            y=y;
            p= p + 2*x + 1;
        }else{
            x++;
            y--;
            p = p + 2*x - 2*y +1;
        }
    }    
}

void filledCircle(int rad, SDL_Renderer *rndr, int centerX, int centerY){
    for(int y = -rad; y <= rad; y++){
        for(int x = -rad; x<= rad; x++){
            if(x*x + y*y <= rad*rad){
                SDL_RenderDrawPoint(rndr, centerX + x, centerY + y);
            }
        }
    }
}

