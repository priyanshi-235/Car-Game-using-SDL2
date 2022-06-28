#ifndef GameWindow_h_
#define GameWindow_h_

//SDL
#include "/SDL2/SDL_image.h"
#include "/SDL2/SDL.h"
#include "/SDL2/SDL_ttf.h"

#include<iostream>


#include "Point.h"  //for coordinate system
#include "Draw.h"
#include "Car.h"

using namespace std;

class GameWindow{
    private:
        int count;
        bool isRunning;

        SDL_Window *window;

    public:

        //SCREEN DIMENSIONS
        const int SCREEN_WIDTH  = 800;  //600
        const int SCREEN_HEIGHT = 650; 

        SDL_Renderer *renderer;

    
        GameWindow();
        ~GameWindow();

        void init(const char* Title, int Xpos, int Ypos, int Width, int Heigth, bool FullScreen);
        void handleEvents();
        void update();
        void render();
        void clean();
        bool running();

        friend void CreateTexture(int, GameWindow &GW);
        friend void initWindow(GameWindow &GW);
};









GameWindow :: GameWindow(){
    //count = 0;
}

GameWindow :: ~GameWindow(){

}

void GameWindow :: init(const char* Title, int Xpos, int Ypos, int Width, int Heigth, bool FullScreen){
    int flags = 0;

    if(FullScreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){ //successfully initialised SDL
        cout<<"\nSDL initialised\n";

        window = SDL_CreateWindow(Title, Xpos, Ypos, Width, Heigth, flags);
        if(window){
            cout<<"\nWindow created\n";
        }else{
            cout<<"\nWindow NOT created\n";
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   //white bkgrd

            cout<<"\nRenderer created\n";
        }else{
            cout<<"\nRenderer NOT created\n";
        }

        //IInitialize the TTF engine , returns -1 on error
        if( TTF_Init() < 0){
            cout<<"\n\n> TTF! SDL_Error: "<<SDL_GetError()<<"\n\n";
        }else{
            cout<<"\nTTF initialised";
        }

        

        isRunning = true;
    }else{
        cout<<"\nSDL NOT initialised\n";
        isRunning = false;
    }

}

void GameWindow :: handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:{
            isRunning = false;
        }break;
        default: break;
    }
}

void GameWindow :: update(){

    //car->Update();
}

void GameWindow :: render(){
    SDL_RenderClear(renderer);
    //SDL_RenderCopy(renderer, CarTex, NULL, &destR);

    //car->Render();

    SDL_RenderPresent(renderer);
}

void GameWindow :: clean(){
    SDL_DestroyWindow(window);
    cout<<"\nWindow destroyed\n";

    SDL_DestroyRenderer(renderer);
    cout<<"\nRenderer destroyed\n";

    //assigning the freed surfaces null
    window = NULL;
    renderer = NULL;

    //Unloads libraries loaded with IMG_Init
    IMG_Quit();

    //Clean up all initialized subsystems
    SDL_Quit();

    cout<<"\n\tDeallocated";
    cout<<"\n\tQuit SDL";

    cout<<"\nGame CLEANED\n";
}

bool GameWindow :: running(){
    return isRunning;
}





#endif
