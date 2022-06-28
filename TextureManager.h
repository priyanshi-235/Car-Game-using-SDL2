#ifndef TextureManager_h_
#define TextureManager_h_

//SDL LIBRARIES
#include "/SDL2/SDL.h"
#include "/SDL2/SDL_image.h"
#include "/SDL2/SDL_ttf.h"

//HEADERS
#include "Point.h"
#include "GameWindow.h"

#include <iostream>

using namespace std;

//#include "Game.h"

class TextureManager{
    private:

        TTF_Font *font = NULL;

        SDL_Color textColor = {255,255,255};        //white 

    public:
        TextureManager();

        SDL_Texture* texture;
        int w, h;

        TextureManager *Load_Image_Texture(const char *Pic, SDL_Renderer *ren);

        SDL_Texture *Load_Text_Texture(const char *text, SDL_Renderer *ren);
};

TextureManager *TextureManager :: Load_Image_Texture(const char *Pic, SDL_Renderer *ren){
    TextureManager *tex;
    
    SDL_Surface *tempSurface = IMG_Load(Pic);
    
    if(tempSurface == NULL){
        cout<<"\n\n> Img failed to load to surface SDL_Error: "<<SDL_GetError()<<"\n\n";
    }else{
        cout<<"\nImg loaded to surface";
        
        w = tempSurface->w;
        h = tempSurface->h;

        texture = SDL_CreateTextureFromSurface(ren, tempSurface);

        if(texture == NULL){     //returns null on failure
            cout<<"\n\n> CreateTextureFromSurface texture SDL_Error: "<<SDL_GetError()<<"\n\n";
        }else{
            cout<<"\nCreated texture";

            SDL_FreeSurface(tempSurface);
            tempSurface = NULL;

            return tex;
        }
    }

    return NULL;
}

SDL_Texture *TextureManager :: Load_Text_Texture(const char *text, SDL_Renderer *ren){
    font = TTF_OpenFont("superstar.ttf",50);
    
    SDL_Surface *tempSurface = TTF_RenderText_Solid(font, text, textColor);
    
    if(tempSurface == NULL){
        cout<<"\n\n> Text couldnt be rendered on the surface! SDL_Error: "<<SDL_GetError()<<"\n\n";  
    }else{
        cout<<"\n\tText rendered on the surface";

        SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tempSurface);

        if(tex == NULL){     //returns null on failure
            cout<<"\n\n> Text Texture couldnt be created! SDL_Error: "<<SDL_GetError()<<"\n\n";  
        }else{
            cout<<"\n\tText Texture created";

            SDL_FreeSurface(tempSurface);
            tempSurface = NULL;

            return tex;
        }
    }

    return NULL;
}

#endif
