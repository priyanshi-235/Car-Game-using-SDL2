#ifndef Point_h_
#define Point_h_


int min(int x, int y);  //returns the minimum value among the 2 passed arguments
int max(int x, int y);  //returns the maximum value among the 2 passed arguments

//Coordinate system
class Coord{
    int x, y, z;
    
    public:    
        Coord();    
        Coord(int, int, int);

        void set(int, int, int);

        int getX();
        int getY();
        int getZ();

        void setX(int);
        void setY(int);
        void setZ(int);

        void increementX(int);
        void increementY(int);
};

Coord :: Coord(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Coord :: Coord(int x, int y, int z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Coord :: set(int x, int y, int z){
    this->x = x;
    this->y = y;
    this->z = z;
}

int Coord :: getX(){
    return x;
}

int Coord :: getY(){
    return y;
}

int Coord :: getZ(){
    return z;
}

void Coord :: setX(int x){
    this->x = x;
}

void Coord :: setY(int y){
    this->y = y;
}

void Coord :: setZ(int z){
    this->z = z;
}

void Coord :: increementY(int speed){
    y = y + speed;
}

void Coord :: increementX(int speed){
    x = x + speed;
}


int min(int x, int y){  //returns the minimum of the passed arguments
    if(x > y){
        return y;
    }
    return x;
}

int max(int x, int y){  //returns the maximum of the passed arguments
    if(x < y){
        return y;
    }
    return x;
}


#endif 