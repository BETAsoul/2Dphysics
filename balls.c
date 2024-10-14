//----------Header files----------
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

//----------CONSTANTS----------
#define ACC 9
#define FPS 30

//----------variables----------
int delTime = 1/FPS;

typedef struct{
    float posx;
    float posy;
}position;

typedef struct{
    float velx;
    float vely;
}velocity;

//----------Functions----------

//Function for drawing circle
void drawCircle(int radius, SDL_Renderer *rndr, int centerX, int centerY){
    float p = 1.25 - radius;
    int x = 0;
    int y = radius;

    while(x<y){
        SDL_RenderDrawPoint(rndr, centerX +x, centerY - y);
        SDL_RenderDrawPoint(rndr, centerX +x, centerY + y);
        SDL_RenderDrawPoint(rndr, centerX -x, centerY - y);
        SDL_RenderDrawPoint(rndr, centerX -x, centerY + y);
        SDL_RenderDrawPoint(rndr, centerX +y, centerY + x);
        SDL_RenderDrawPoint(rndr, centerX +y, centerY - x);
        SDL_RenderDrawPoint(rndr, centerX -y, centerY - x);
        SDL_RenderDrawPoint(rndr, centerX -y, centerY + x);

        if(p<=0){
            x++;
            y=y;
            p = p +2*x +1;
        }
        else{
            x++;
            y--;
            p = p + 2*x - 2*y +1;
        }
  
    }
}

//Collision handling
void collisionHandle(){}


//------------MAIN------------
int main(int argc, char *argv[]){

    if(SDL_Init(SDL_INIT_VIDEO)<0){
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("2DPhysicsEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    drawCircle(40, renderer, 400, 300);

    SDL_RenderPresent(renderer);

    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
