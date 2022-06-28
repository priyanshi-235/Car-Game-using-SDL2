#ifndef Road_h_
#define Road_h_

#include "/SDL2/SDL.h"
#include "/SDL2/SDL_image.h"
#include "Point.h"  //for coordinate system


class Road{
    protected:
    
        SDL_Texture *objTexture;
        SDL_Rect srcRect, destRect;
        SDL_Renderer *renderer;

    public:
    
        //STARTING POSITIONS
        const int startX = 150; //1/4 from left
        const int startY = 0;   //top

        //FINISHING POSITION
        const int finishX = 380;
        const int finishY = 490;
    
        Coord pos;

        Road();
        Road(const char *textureSheet, SDL_Renderer *ren);
        ~Road();

        void Update();
        void Update_Position(int);
        void Render();

};

void Road :: Update_Position(int speed){
    pos.setY(pos.getY() - speed);

    if(pos.getY() <= 2){
        pos.setY(550);
    }
}


void Road :: Update(){
    pos.set(0,0,0);

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = pos.getX();
    destRect.w = pos.getY();
    destRect.x = srcRect.w * 2;
    destRect.y = srcRect.h * 2;
}

void Road :: Render(){
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}


#endif
