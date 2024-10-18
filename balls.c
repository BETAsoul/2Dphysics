#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include "circles.h"

#define FPS 60
#define MAX_VELOCITY 450

float delTime = 1.00/FPS;

int main(int argc, char *argv[]){

    if(SDL_Init(SDL_INIT_VIDEO)<0){
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("2DPhysicsEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;

    int running = 1;
    circle c1;
    c1.posX = 70;
    c1.posY = 60;
    c1.accX = 0.50;
    c1.accY = 1.00;
    c1.velX = 20.00;
    c1.velY = 20.00;
    c1.radius = 40;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if(c1.posX - c1.radius <= 0 || c1.posX + c1.radius >= 800){
            c1.velX = -c1.velX;
        }
        if (c1.posY - c1.radius <= 0 || c1.posY + c1.radius >= 600) {
            c1.velY = -c1.velY;
        }

        c1.posX = c1.posX + c1.velX*delTime;
        c1.posY = c1.posY + c1.velY*delTime;
        c1.velX = c1.velX + c1.accX*delTime;
        c1.velY = c1.velY + c1.accY*delTime;

        if (c1.velX > MAX_VELOCITY) c1.velX = MAX_VELOCITY;
        if (c1.velY > MAX_VELOCITY) c1.velY = MAX_VELOCITY;
        if (c1.velX < -MAX_VELOCITY) c1.velX = -MAX_VELOCITY;
        if (c1.velY < -MAX_VELOCITY) c1.velY = -MAX_VELOCITY;
     
        SDL_SetRenderDrawColor(renderer, 170, 100,150,  255);
        filledCircle(c1.radius, renderer, c1.posX, c1.posY);
        SDL_RenderPresent(renderer);

        SDL_Delay(delTime);

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
