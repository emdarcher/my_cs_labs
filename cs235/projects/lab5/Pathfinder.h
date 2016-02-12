
#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "PathfinderInterface.h"
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>


#define DOES_NOT_EXIST -1
#define DIM_CELLS   5

#define STR_BUFF_SIZE 128

#define PRINT_INFO 0

class Pathfinder : public PathfinderInterface {
    private:
        string maze;
        uint8_t rand_bool(void);
        char num_to_char(int num);
        int char_to_num(char ch);
        void edit_maze(string& in_maze, int val, int x, int y, int z);
        int get_maze_val(string& in_maze, int x, int y, int z);
        int coordinates_to_index(int x, int y, int z);
        void generate_maze(string& in_maze);
        int count_file_lines(string in_file_name);
        bool is_int_num(string str);
        string coordinates_to_string(int x, int y, int z);
        int search_path(vector<string>& in_path, string coord_str);
        bool rec_solve_maze(string& in_maze, vector<string>& in_path, 
                int x, int y, int z);
    public:
        Pathfinder();
        virtual ~Pathfinder();
		virtual string getMaze();
		virtual void createRandomMaze();
		virtual bool importMaze(string file_name);
		virtual vector<string> solveMaze();
};

#endif
