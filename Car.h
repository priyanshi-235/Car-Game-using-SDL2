#ifndef Car_h_
#define Car_h_

#include "/SDL2/SDL.h"
#include "/SDL2/SDL_image.h"

#include "Point.h"  //for coordinate system
#include "GameWindow.h"
#include "Road.h"

//--------------------------------C A R     C L A S S---------------------------------------

class Car{
    protected:

        SDL_Texture *objTexture;
        SDL_Rect srcRect, destRect;
        SDL_Renderer *renderer;

    public:
        
        //CAR DIMENSIONS
        const int carHeight = 160;
        const int carWidth = 70;
    
        Coord pos;

        Car(const char *textureSheet, SDL_Renderer *ren);
        ~Car();

        void Update();
        void Render();
};

//-------------------------------U S E R - C A R  C L A S S---------------------------------------

class User_Car: public Car{
    public:
        User_Car(GameWindow &GW, char *picName = "Pictures/car.png") : Car(picName, GW.renderer){};

        void Update_Position(Road *R);
};

//------------------------------P O L I C E - C A R  C L A S S---------------------------------------

class Police_Car: public Car{
    public:
        Police_Car :: Police_Car(GameWindow &GW) : Car("Pictures/police.png",GW.renderer){};

        void Update_Position(Road *R, int level);

        friend bool Game :: createCar(int x, int y);
};


//-------------------------------C A R      F X N S ---------------------------------------


Car :: Car(const char* textureSheet, SDL_Renderer *ren){
    renderer = ren;
    TextureManager CarTexture;
    objTexture = CarTexture.Load_Image_Texture(textureSheet, ren)->texture;
    pos.set(0,0,0);
}

void Car :: Update(){
    pos.set(0,0,0);

    // srcRect.h = 32;
    // srcRect.w = 32;
    // srcRect.x = 0;
    // srcRect.y = 0;

    destRect.x = pos.getX();
    destRect.y = pos.getY();
    destRect.w = carWidth;
    destRect.h = carHeight;
}

void Car :: Render(){
    SDL_RenderCopy(renderer, objTexture, NULL, &destRect);
}


//---------------------U S E R     C A R    F X N S---------------------------------------

void User_Car :: Update_Position(Road *R){
    pos.setX( max( pos.getX() , R->startX ) );
    pos.setY( max( pos.getY() , R->startY ) );

    pos.setX( min( pos.getX() , R->finishX ) );
    pos.setY( min( pos.getY() , R->finishY ) );
}

//---------------------P O L I C E     C A R    F X N S---------------------------------------

void Police_Car :: Update_Position(Road *R, int level){
    Game G;
    if(pos.getY() > R->finishY + carHeight){
            int x, y;
            while(true){
                x = ((rand()/10)% (R->finishX - R->startX)) + R->startX ;
                y = -(rand() % ((R->finishY - R->startY) * 10 * (level+1))) ;
                
                if(G.createCar(x,y)){     
                    break;
                }
            }
            int z = rand()%2;

            pos.setX(x);
            pos.setY(y);
            pos.setZ(z);
        }
}

#endif
