
#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "PathfinderInterface.h"
#include <stdlib.h>
#include <stdint.h>
#include <iostream>

#define DOES_NOT_EXIST -1
#define DIM_CELLS   5


class Pathfinder : public PathfinderInterface {
    private:
        string maze;
        uint8_t rand_bool(void);
        char num_to_char(int num);
        void edit_maze(string& in_maze, int val, int x, int y, int z);
        int coordinates_to_index(int x, int y, int z);
        void generate_maze(string& in_maze);
    public:
        Pathfinder();
        virtual ~Pathfinder();
		virtual string getMaze();
		virtual void createRandomMaze();
		virtual bool importMaze(string file_name);
		virtual vector<string> solveMaze();
};

#endif
