
#include "Pathfinder.h"


Pathfinder::Pathfinder(){
    //seed random number generator
    srand(time(0));
}
Pathfinder::~Pathfinder(){}



char Pathfinder::num_to_char(int num){
    return (char)(num + '0');
}
int Pathfinder::char_to_num(char ch){
    return (int)(ch - '0');
}

void Pathfinder::edit_maze(string& in_maze, int val, int x, int y, int z){
    int index = coordinates_to_index(x, y, z);
    if(index != DOES_NOT_EXIST){
        in_maze[index] = num_to_char(val); 
    } 
}
int Pathfinder::get_maze_val(string& in_maze, int x, int y, int z){
    int index = coordinates_to_index(x, y, z);
    if(index != DOES_NOT_EXIST){
        return char_to_num(in_maze[index]); 
    } 
    //if it doesn't exist return 0
    //so the algorithm doesn't try to access it
    return 0;
    //return DOES_NOT_EXIST;
}

#define CHAR_PER_ROW (DIM_CELLS*2)
#define ROWS_PER_GRID DIM_CELLS

int Pathfinder::coordinates_to_index(int x, int y, int z){
    int z_base = 0;
    int y_base = 0;
    int x_base = 0;
    //check that the coordinates are within ranges
    if(!( ((x >= 0)&&(x < DIM_CELLS)) 
                && ((y >= 0)&&(y < DIM_CELLS)) 
                && ((z >= 0)&&(z < DIM_CELLS)) )){
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
    for(int z=0;z<DIM_CELLS;z++){
        for(int y=0;y<DIM_CELLS;y++){
            for(int x=0;x<DIM_CELLS;x++){
                in_maze += "1";
                in_maze += (x != (DIM_CELLS-1) ) ? " " : "\n"; 
            }
        }
        if(z != (DIM_CELLS-1)){
            in_maze += "\n";
        }
    }
}

string Pathfinder::getMaze(){
    //if no maze has been made
    //generate a new maze and return it
    if(maze.length() == 0){
        generate_maze(maze); 
        return maze;
    }
    return maze;
}

uint8_t Pathfinder::rand_bool(void){
    //returns randomly 1 or 0
    //using a bitwise AND on the random int
    //to get the last bit
    unsigned int in_rand = rand();
    return (in_rand & 0x01);
}
void Pathfinder::createRandomMaze(){
    //generate all 1's maze to start with
    generate_maze(maze);
    //loop through all maze spots and insert a random value.
    for(int z=0;z<DIM_CELLS;z++){
        for(int y=0;y<DIM_CELLS;y++){
            for(int x=0;x<DIM_CELLS;x++){
                edit_maze(maze, (int)rand_bool(), x, y, z);        
            }
        }
    }
    //put 1's in the enterance and exit slots
    edit_maze(maze, 1, 0, 0, 0);
    edit_maze(maze, 1, DIM_CELLS-1, DIM_CELLS-1, DIM_CELLS-1); 
    //debugging
    //cout << "created random maze:\n" << maze << "\n";
}
int Pathfinder::count_file_lines(string in_file_name){
    int lc = 0;
    string linestr = "";
    ifstream in_file(in_file_name);
    if(in_file.is_open()){
        while(getline(in_file, linestr, '\n')){
            ++lc; 
        }
        in_file.close();
        return lc;
    }
    return DOES_NOT_EXIST;
}

bool Pathfinder::is_int_num(string str){
    for(int i=0;i<str.length();i++){
        //cout << "check isdigit(\'" << str[i] << "\')\n";
        if(!isdigit(str[i])){
            return false;
        }
    }
    return true;
}
bool Pathfinder::importMaze(string file_name){
    int mazeFile_lc = count_file_lines(file_name);
    if(mazeFile_lc == DOES_NOT_EXIST){
        //check if the file exists
        return false;
    } else if(mazeFile_lc != (DIM_CELLS * DIM_CELLS + (DIM_CELLS-1))){
        //check for correct number of lines
        return false;
    }

    //using temporary maze so we don't alter the global maze
    //if the input is invalid
    string tmp_maze;
    //generate new maze
    generate_maze(tmp_maze);

    ifstream mazeFile(file_name);
    int in_number = -1;    
    string in_num_str;

    for(int z=0;z<DIM_CELLS;z++){
        for(int y=0;y<DIM_CELLS;y++){
            for(int x=0;x<DIM_CELLS;x++){
                if(mazeFile >> in_num_str){
                    if(is_int_num(in_num_str)){
                        in_number = stoi(in_num_str);
                        if((in_number == 0) || (in_number == 1)){
                            edit_maze(tmp_maze, in_number, x, y, z);
                        } else {
                            mazeFile.close();
                            return false;
                        }
                    } else {
                        mazeFile.close();
                        return false;
                    }
                } else {
                    mazeFile.close();
                    return false;
                }     
            }
        }
    }

    if((get_maze_val(tmp_maze, 0, 0, 0) != 1) 
            || (get_maze_val(tmp_maze, DIM_CELLS-1, DIM_CELLS-1, DIM_CELLS-1) != 1)){
        //check for 1's at the start and end 
        return false; 
    }

    //if there were no errors, copy the temporary maze to the current maze    
    maze.clear();
    maze += tmp_maze; 

    mazeFile.close();
    return true;

}

string Pathfinder::coordinates_to_string(int x, int y, int z){
    stringstream coordinate_ss;
    coordinate_ss << "(" << x << ", " << y << ", " << z << ")";
    return coordinate_ss.str();
}


//returns index of matching coordinates in the path
//or returns DOES_NOT_EXIST if a match doesn't exist
int Pathfinder::search_path(vector<string>& in_path, string coord_str){
    for(int i=0;i<in_path.size();i++){
        if(in_path[i] == coord_str){
            return i;
        }
    }
    return DOES_NOT_EXIST;
}

vector<string> Pathfinder::solveMaze(){
    vector<string> path;
    //the recursive function has to ignore previously failed paths and loops
    //
#if PRINT_INFO
    cout << "starting new maze!\n";
    cout << maze << "\n";
#endif
    //add the string "start" to the path
    //to tell the recursive function that it is on it's first call
    path.push_back("start");
    //call the recursive solving function
    if(rec_solve_maze(maze, path, 
                0, 0, 0)){
        return path;
    }
    //otherwise it is not solvable
    //so clear path and return
    path.clear();
    return path;
}

//create recursive funtion to solve that maze
//returns bool, true if solvable, false if unsolvable
//takes a vector<string> reference and modifies it in each successful call
//with the path coordinates
//
bool Pathfinder::rec_solve_maze(string& in_maze, vector<string>& in_path,
        int x, int y, int z){
    //vector to store cells already visited and failed
    static vector<string> visited;

#if PRINT_INFO 
    static int calls_cnt = 0;
    calls_cnt++;
    bool original_call = false;
#endif
    if(get_maze_val(in_maze, x, y, z) == 0){
        return false;
    }
    if(in_path.back() == "start"){
#if PRINT_INFO
        cout << "detected start\n";
        calls_cnt = 0;
        original_call = true;
#endif
        in_path.pop_back();
        visited.clear();
    }
    string my_coord_str = coordinates_to_string(x, y, z);
    int my_index = search_path(in_path, my_coord_str);
    int visited_i = search_path(visited, my_coord_str);
    //if we have been to this location before, then return false
    if((my_index != DOES_NOT_EXIST)||(visited_i != DOES_NOT_EXIST)){
        return false;
    }

    //add the current coordinates to the path
    in_path.push_back(my_coord_str);
    //cout << "added " << my_coord_str << " to the path\n";
    
    
    //if we are at the end of the maze return true
    if((x==DIM_CELLS-1)&&(y==DIM_CELLS-1)&&(z==DIM_CELLS-1)){
#if PRINT_INFO
        cout << "maze is: SOLVABLE\n";
        cout << "took " << calls_cnt << " calls to solve.\n\n";
#endif
        return true;
    }

    //call recursively to see if any paths are solvable
    if(rec_solve_maze(in_maze, in_path, x+1, y, z)
            || rec_solve_maze(in_maze, in_path, x-1,y,z)
            || rec_solve_maze(in_maze, in_path, x,y+1,z)
            || rec_solve_maze(in_maze, in_path, x,y-1,z)
            || rec_solve_maze(in_maze, in_path, x,y,z+1)
            || rec_solve_maze(in_maze, in_path, x,y,z-1)
            ){
        return true;   
    } else {
        //cout << "removing " << in_path.back() << " from the path\n";
        visited.push_back(in_path.back());
        //cout << "visited.size() == " << visited.size() << "\n";
        in_path.pop_back();
       
#if PRINT_INFO 
        if(original_call){
            cout << "maze is: IMPOSSIBLE\n";
            cout << "took " << calls_cnt << " calls to solve.\n\n";
        } 
#endif
        return false;
    } 
    return false;
}


