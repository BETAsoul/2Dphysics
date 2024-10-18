#ifndef circles
#define circles
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>

typedef struct{
    int posX;
    int posY;
    float accX;
    float accY;
    float velX;
    float velY;
    int radius;
} circle;


void drawCircle(int rad, SDL_Renderer *rndr, int centerX, int centerY);
void filledCircle(int rad, SDL_Renderer *rndr,int centerX, int centerY);


#endif
