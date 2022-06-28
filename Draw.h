#ifndef Draw_h_
#define Draw_h_

#include <iostream>
#include <string>

//SDL LIBRARIES
#include "/SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "/SDL2/SDL_ttf.h"

//HEADERS
#include "Point.h"
#include "GameWindow.h"
#include "TextureManager.h"

using namespace std;

enum Pictures { roadPNG, carPNG, policePNG, startPNG, endPNG};

class Draw{         //creates texture of the pictures
    private:

        

    public:
        //Loads individual image as texture
        TextureManager *Pics[5];

        void initWindow(GameWindow &GW);

        //Loads media
        void loadMedia(int n, Coord srcCoord, Coord destCoord, GameWindow &GW);

        void CreateTexture(int n, GameWindow &GW);

        void printText(string text, int x, int y, GameWindow &GW);
};

void Draw :: initWindow(GameWindow &GW){
        for(int i = 0; i <= 4; i++){
            CreateTexture(i, GW);
        }
}

void Draw :: CreateTexture(int n, GameWindow &GW){
    switch (n){ //0-road, 1-car, 2-ppolice, 3-start, 4-end
        case roadPNG:{
            Pics[n] = Pics[n]->Load_Image_Texture("Pictures/road2.png", GW.renderer);
        }break;

        case carPNG:{
            Pics[n] = Pics[n]->Load_Image_Texture("Pictures/car.png", GW.renderer);
        }break;

        case policePNG:{
            Pics[n] = Pics[n]->Load_Image_Texture("Pictures/police.png", GW.renderer);
        }break;

        case startPNG:{
            Pics[n] = Pics[n]->Load_Image_Texture("Pictures/start.png", GW.renderer);
        }break;

        case endPNG:{
            Pics[n] = Pics[n]->Load_Image_Texture("Pictures/end.png", GW.renderer);
        }break;
        
        default:
            break;
    }   
}


void Draw :: printText(string text, int x, int y, GameWindow &GW){
    TextureManager PictureTexture;
   
    const char *Txt = text.c_str();

    SDL_Texture *TextTexture = PictureTexture.Load_Text_Texture(Txt, GW.renderer);
    
    int Txt_lt = text.size();

    SDL_Rect dest;
    dest.x = x + (10*(5-Txt_lt));
    dest.y = y;
    dest.w = 20*Txt_lt;
    dest.h = 50;

    if(SDL_RenderCopy(GW.renderer, TextTexture, NULL, &dest) < 0){
        cout<<"\n\n> Text couldnt be rendered on the surface! SDL_Error: "<<SDL_GetError()<<"\n\n";  
    }else{
        cout<<"\n\tCopy a portion of the texture to the current rendering target";
    }

    SDL_DestroyTexture(TextTexture); 
}



void Draw :: loadMedia(int n, Coord srcCoord, Coord destCoord, GameWindow &GW){

    SDL_Rect srcRect = { 
                            srcCoord.getX(), srcCoord.getY(),
                            min(GW.SCREEN_WIDTH, Pics[n]->w),
                            min(GW.SCREEN_HEIGHT, Pics[n]->h)
                        };

    SDL_Rect destRect = { 
                            destCoord.getX(), destCoord.getY(),
                            min(GW.SCREEN_WIDTH, Pics[n]->w),
                            min(GW.SCREEN_HEIGHT, Pics[n]->h)
                        };  
    
    //the texture will be stretched to fill the given rectangle

    //Copy a portion of the texture to the current rendering target
    if( SDL_RenderCopy( GW.renderer, Pics[n]->texture, &srcRect, &destRect) < 0){
        cout<<"\n\n> Texture couldnt be rendered! SDL_Error: "<<SDL_GetError()<<"\n\n";  
    }else{
        cout<<"\n\tTexture rendered";
    }

}


#endif
