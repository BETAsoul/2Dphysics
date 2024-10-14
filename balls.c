//----------Header files----------
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

//----------CONSTANTS----------
#define ACC 0.01
#define FPS 60
#define MAX_VELOCITY 100

//----------variables----------
float delTime = 1.00/FPS;

typedef struct{
    float posX;
    float posY;
}position;

typedef struct{
    float velX;
    float velY;
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
        SDL_RenderDrawPoint(rndr, centerX +y, centerY - x);
        SDL_RenderDrawPoint(rndr, centerX +y, centerY + x);
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


//------------MAIN------------
int main(int argc, char *argv[]){

    if(SDL_Init(SDL_INIT_VIDEO)<0){
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("2DPhysicsEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;
    int running = 1;

    int radius = 40;

    velocity vel;
    vel.velX = 70;
    vel.velY = 85;

    position pos;
    pos.posX = 50;
    pos.posY = 50;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if(vel.velX>MAX_VELOCITY)vel.velX = MAX_VELOCITY;
        if(vel.velY>MAX_VELOCITY)vel.velY = MAX_VELOCITY;

        if(pos.posX - radius <= 0 || pos.posX + radius >= 800){
            vel.velX = -vel.velX;
        }
        if (pos.posY - radius <= 0 || pos.posY + radius >= 600) {
            vel.velY = -vel.velY;
        }
       
        
        vel.velX = vel.velX + ACC*vel.velX;
        vel.velY = vel.velY + ACC*vel.velY;
       
        pos.posX = pos.posX + vel.velX*delTime;
        pos.posY = pos.posY + vel.velY*delTime;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0,  255);
        drawCircle(radius, renderer, pos.posX, pos.posY);
        SDL_RenderPresent(renderer);

        SDL_Delay(1000/FPS);

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
