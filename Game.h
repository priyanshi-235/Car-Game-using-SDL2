
#ifndef Game_h_         
#define Game_h_   

//SDL LIBRARIES
#include "/SDL2/SDL.h"
#include "/SDL2/SDL_image.h"

//HEADERS
#include "Draw.h"   //uses sdl to display car and background and level and score on the screen
#include "Point.h"  //for coordinate system
#include "Road.h"
#include "Car.h"
#include "GameWindow.h"

using namespace std;


//-------------------G A M E    C L A S S-------------------------
class Game{
    GameWindow GW;
    
    Police_Car **P;
    User_Car *C;

    Road *R;

    int speed;

    const int NoOfPoliceCar = 5;
    
    
    
    const int targetScore[4] = {20, 40, 70, 7000};
    //
    int score;  //acc to the game clock
    int level;  //acc to score

    int moveStep;

    bool played;
    bool endGame;       //game has ended
    bool restart;
    int startTime;
    
    

    public:

        //CONSTRUCTOR
        Game();

        void start_Screen();
        void end_Screen();

        //Initialises the game screen 
        void Initialise();

        //
        void Run();

        //updates the screen
        void Update();

        //creates the car
        bool createCar(int x, int y);

    private:

        void Update_Score();

        //checks position of the car and screen
        void checkPos();

        //checks whether the police car and user car have collided
        bool Collision();

        //renders the game screen
        void render();

        //displays the level and score
        void Print_ScoreAndLevel();
};












//-------------------G A M E    C L A S S   F X N S-------------------------

//GAME CLASS CONSTRUCTOR
Game :: Game(){
    C = new User_Car(GW);

    cout<<"\nGame::Constructor called";

    //spedd of car
    speed = 4;

    P = new Police_Car*[NoOfPoliceCar];

    
    R->pos.set(0,550,0);

    //position of car
    C->pos.set(250,400,400);

    //initialising score and level to 0
    score = 0;
    level = 0;

    moveStep = 20;
    
    played = false;
    endGame = false;
    restart = true;


    cout<<"\nGame::Constructor ---\n";
}

void Game :: Initialise(){
    cout<<"\nGame::Init called";

    for(int i = 0; i < NoOfPoliceCar; i++){
        P[i]->pos.setY(R->finishY + 1000);
    }

    speed = 3;

    //position 
    R->pos.set(0,550,0);

    //position of car
    C->pos.set(250,400,0);
    
    //initialising score and level of game to 0
    score = 0;
    level = 0;

    moveStep = 20;

    endGame = false;
    restart = false;

    //recording the time at which game begins
    startTime = clock();    //returns the approx processor time that is consumed by the program

    cout<<"\nGame::Init ---\n";
}






//-----------------------------S T A R T    S C R E E N------------------------------------------------

void Game :: start_Screen(){
    cout<<"\nstartGame called";
    Draw StartFrame;

    Coord p0;
    StartFrame.loadMedia(startPNG, p0, p0, GW);     //loads start.png

    //Update the screen with any rendering performed since the previous call
    SDL_RenderPresent( GW.renderer );
    cout<<"\n\tStart screen presented";

    cout<<"\nstartGame ---\n";
}
//-------------------------------E N D    S C R E E N----------------------------------------------

void Game :: end_Screen(){
    cout<<"\nendGame called";
    Draw EndFrame;

    Coord p0;
    EndFrame.loadMedia(endPNG, p0, p0, GW);    //loads end.png
    
    SDL_RenderPresent(GW.renderer);
    cout<<"\n\tEnd screen presented";

    cout<<"\nendGame ---\n";
}




void Game :: Update_Score(){
    if(!endGame){
        cout<<"\n\tUpdates score";
        score = ((clock() - startTime) / (double) CLOCKS_PER_SEC);  //yields the number of seconds 
    }
}





void Game :: render(){
    
    cout<<"\nGame::Render called";

    Update_Score();

    C->Render();

    Coord p0;

    // loadMedia(carPNG, p0, posCar);   //loads texture[1] ie car.png , from source rect(0,0) to dest rect(posCar)
    // cout<<"\n\tRenders car at (0,0)";

    //0-road, 1-car, 2-police, 3-start, 4-end
    Draw D;
    
    for(int i = 0; i < NoOfPoliceCar; i++){    //numCar = 5
        if(
            P[i]->pos.getY() + C->carHeight >= R->startY 
            && P[i]->pos.getY() <= R->finishY + C->carHeight
        ){
            D.loadMedia(policePNG, p0, P[i]->pos, GW);    //P[i]->pos.getZ() + 5
        }
    }

    Print_ScoreAndLevel();

    GW.render();

}

//----------------------------D I S P L A Y S   S C O R E   &   L E V E L----------------------------


/*
    SCREEN_WIDTH  = 600
    SCREEN_HEIGHT = 650

    carHeight = 160
    arWidth = 70
*/

void Game :: Print_ScoreAndLevel(){
    Draw D;
   
    cout<<"\nGame::Print called";

    string text;

    text = "LEVEL";

    D.printText(text, 24, 240, GW);       //displays: LEVEL   at(24,240)
    

    cout<<"\n\tLevel displayed";

    text = "SCORE";

    D.printText(text, 470, 240, GW);      //displays: SCORE   at(470,240)
    

    cout<<"\n\tScore displayed";

    char buffer[100];

    SDL_itoa(level+1,buffer,10);    //converts the integer(level+1) acc to base10 to string(buffer)

    text = string(buffer);

    D.printText(text, 24, 290, GW);         //displays: LevelNo     at(24,290)
    

    SDL_itoa(score, buffer, 10);     //converts the integer(score) acc to base10 to string(buffer)

    text = string(buffer);

    D.printText(text, 470, 290, GW);      //displays: ScoreNo     at(470,290)
    

    cout<<"\nGame::Print ---\n";
    
}

/*

LEVEL(24,290)   LevelNo(24,290)     on left side one below the other

SCORE(470,240)  ScoreNo(470,290)    on right side one below the other

*/

void Game :: checkPos(){
    
    cout<<"\nGame::CheckPos called";

    R->Update_Position(speed);
    C->Update_Position(R);

    // posCar.x = max(posCar.x, startX);
    // posCar.y = max(posCar.y, startY);
    // posCar.x = min(posCar.x, finishX);
    // posCar.y = min(posCar.y, finishY);

    cout<<"\nGame::CheckPos ---\n";

}

#include "Game.h"

bool Game :: createCar(int x, int y){

    cout<<"\nGame::CreateCar";

    for(int i = 0; i < NoOfPoliceCar; i++){        //numCar = 5
        if(
            P[i]->pos.getY() < 0 && ((y<=P[i]->pos.getY() && P[i]->pos.getY() <= y + 4 * C->carHeight) 
            || 
            (P[i]->pos.getY() <= y && y<=P[i]->pos.getY()+4* C->carHeight))
        ){
            if(abs(x-P[i]->pos.getX()) < 2*C->carHeight){
                return false;
            }
        }
    }
    return true;
  
}

void Game :: Update(){
   
    cout<<"\nGame::Update called";

    for(int i = 0; i < NoOfPoliceCar; i++){    //numcar=5
        P[i]->Update_Position(R, level);
    }

    for(int i = 0; i < NoOfPoliceCar; i++){
        P[i]->pos.increementY(+speed);
    }

    if(score >= targetScore[level]){
        level++;
        cout<<"\n\tLevel increased";

        speed += 3;
        moveStep += 10;
        cout<<"\n\tSpeed increased";

        R->pos.setY(550);
    }

    cout<<"\nGame::Update ---\n";

}

//-------------------------------C O L L I S I O N-----------------------------------

bool Game :: Collision(){
    
    cout<<"\nGame::Collsion";

    for(int i = 0; i < NoOfPoliceCar; i++){
        if(

            (
                P[i]->pos.getX() < C->pos.getX()
                && C->pos.getX() < P[i]->pos.getX() + C->carWidth
                && P[i]->pos.getY() < C->pos.getY()
                && C->pos.getY()  < P[i]->pos.getY() + C->carHeight
            )

            ||

            (
                P[i]->pos.getX() < C->pos.getX()
                && C->pos.getX() < P[i]->pos.getX() + C->carWidth
                && P[i]->pos.getY() < C->pos.getY() + C->carHeight
                && C->pos.getY() + C->carHeight< P[i]->pos.getY() + C->carHeight
            )

            ||

            (
                P[i]->pos.getX() < C->pos.getX() + C->carWidth
                && C->pos.getX() + C->carWidth < P[i]->pos.getX() + C->carWidth
                && P[i]->pos.getY() < C->pos.getY()
                && C->pos.getY() < P[i]->pos.getY() + C->carHeight
            )

            ||

            (
                P[i]->pos.getX() < C->pos.getX() + C->carWidth
                && C->pos.getX() + C->carWidth < P[i]->pos.getX() + C->carWidth
                && P[i]->pos.getY() < C->pos.getY() + C->carHeight
                && C->pos.getY() + C->carHeight < P[i]->pos.getY() + C->carHeight
            )

        ){
            cout<<"\n\tCOLLIDED !\n";

            return true;
        }
    }
    return false;

}


//------------------------------R U N    G A M E-----------------------------

/*
In the begining,
    played = false;
    endGame = false;
    restart = true;
*/

void Game :: Run(){
    Draw D;
    
    cout<<"\nGame::Run called";

    srand(time(NULL));
    
    bool quit = false;
    
    SDL_Event e;

    int mouseX, mouseY;

    GW.init("Car Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);   //Starts up SDL and creates window

    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    start_Screen();    //start.png displayed

    while(!quit){       //game screen is displayed until the cross button of game screen is not pressed

        frameStart = SDL_GetTicks();        //records the starting time of the game frame

        while(SDL_PollEvent(&e) != 0){

            //------------------------Q U I T---------------------------------
            if(e.type == SDL_QUIT){     //cross button is pressed
                quit = true;    //the player quits the game
            }

            //------------------P L A Y     G A M E------------------------------
            if(
                played ||                                   //game is being played  //in the beg played = false
                (                                           //OR
                    e.type == SDL_MOUSEBUTTONDOWN           //mouse was clicked
                    && mouseX >=140                         //
                    && mouseY >=465                         //
                    && mouseX <=465                         //
                    && mouseY <=540                         //  (   140-465    ,   465-540  ) yaha par mouse click hua h
                )                        //
            ){
                cout<<"\n\t---------P L A Y I N G--------";

                played = true;      //in the beg played = false
                
                if(restart){    //in the beg restart = true
                    Initialise();     //Initialises the game screen
                }

                //array element with value 1 means that the key is pressed 
                //and a valueof 0 means that it is not
                //shift not considered
                const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
                
                
                if(currentKeyStates[SDL_SCANCODE_UP]){      
                    //up arrow key was pressed
                    C->pos.increementY(-moveStep);  //y-20  //UP

                }else if(currentKeyStates[SDL_SCANCODE_DOWN]){
                    //down arrow key was pressed

                    C->pos.increementY(+moveStep);       //y+20  //DOWN

                }else if(currentKeyStates[SDL_SCANCODE_LEFT]){
                    //left arrow key was pressed

                    C->pos.increementX(-moveStep);      //x-20  //LEFT

                }else if(currentKeyStates[SDL_SCANCODE_RIGHT]){
                    //right arrow key was pressed

                    C->pos.increementX(+moveStep);      //x+20  //RIGHT

                }

                if(endGame){        //in the beg endgaem = false
                    if(
                        e.type == SDL_MOUSEBUTTONDOWN           //restart was clicked
                        && mouseX >=140
                        && mouseY >=465
                        && mouseX <=465
                        && mouseY <=540                 //  (   140-465    ,   465-540  )
                    ){
                        restart = true;         //restart the game
                    }
                }
            }
        }

        //---------------------------U P D A T E     S C R E E N---------------------------------------------
        if(played){
            cout<<"\n\tUpdate Screen";

            checkPos();
            Update();

            if(!endGame){       //game is playing
                render();
            }

            if(!endGame && Collision()){    //2 cars collide
                endGame = true; //game ends
                cout<<"\n\tCOLLISION! Game ended!";

                for(int i = 0; i < 250; i++){
                    render();   //displays the collided cars
                }
            }

            if(endGame){        //game has ended    //cars have collided
                cout<<"\n\tEND GAME displayed";

                end_Screen();     //displays the game over screen
            }

            cout<<"\n\tScreen Updated";
        }

        if(e.type == SDL_MOUSEMOTION){
            mouseX = e.button.x;
            mouseY = e.button.y;
        }

        frameTime = SDL_GetTicks() - frameStart;
        
        if(frameDelay > frameTime){

            //Wait a specified number of milliseconds before returning
            SDL_Delay(frameDelay - frameTime);
        }
    }

    //close();        //Frees media and shuts down SDL
    GW.clean();

    cout<<"\nGame::Run ---\n";
    
}






#endif 
