
#include "Pathfinder.h"


Pathfinder::Pathfinder(){
    //seed random number generator
    srand(time(0));
}
Pathfinder::~Pathfinder(){}



char Pathfinder::num_to_char(int num){
    return (char)(num + '0');
}

void Pathfinder::edit_maze(string& in_maze, int val, int x, int y, int z){
    int index = coordinates_to_index(x, y, z);
    if(index != DOES_NOT_EXIST){
        in_maze[index] = num_to_char(val); 
    } 
}

#define CHAR_PER_ROW 10
#define ROWS_PER_GRID 5

int Pathfinder::coordinates_to_index(int x, int y, int z){
    int z_base = 0;
    int y_base = 0;
    int x_base = 0;
    //check that the coordinates are within ranges
    if(!( ((x >= 0)&&(x < 5)) && ((y >= 0)&&(y < 5)) && ((z >= 0)&&(z < 5)) )){
        return DOES_NOT_EXIST;
    }
   
    //calulate the amount of chars to the beginning of the next grid
    //adding one to compensate for the newline between grids
    z_base = z * (CHAR_PER_ROW * ROWS_PER_GRID + 1);

    y_base = y * (CHAR_PER_ROW);

    x_base = x * (2);

    return z_base + y_base + x_base;
}

void Pathfinder::generate_maze(string& in_maze){
    //clear the maze before adding to it
    in_maze.clear();
    for(int z=0;z<5;z++){
        for(int y=0;y<5;y++){
            for(int x=0;x<5;x++){
                in_maze += "1";
                in_maze += (x != 4) ? " " : "\n"; 
            }
        }
        if(z != 4){
            in_maze += "\n";
        }
    }
}

string Pathfinder::getMaze(){
    if(maze.length() == 0){
        generate_maze(maze); 
        return maze;
    }
    return maze;
}

uint8_t Pathfinder::rand_bool(void){
    unsigned int in_rand = rand();
    return (in_rand & 0x01);
}
void Pathfinder::createRandomMaze(){
    //generate all 1's maze to start with
    generate_maze(maze);
    //loop through all maze spots and insert a random value.
    for(int z=0;z<5;z++){
        for(int y=0;y<5;y++){
            for(int x=0;x<5;x++){
                edit_maze(maze, (int)rand_bool(), x, y, z);        
            }
        }
    }
    //put 1's in the enterance and exit slots
    edit_maze(maze, 1, 0, 0, 0);
    edit_maze(maze, 1, 4, 4, 4); 
    //debugging
    cout << "created random maze:\n" << maze << "\n";
}

bool Pathfinder::importMaze(string file_name){

}

vector<string> Pathfinder::solveMaze(){

}




