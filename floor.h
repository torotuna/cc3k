#ifndef FLOOR_H
#define FLOOR_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "direction.h" // likley wrong, delete
#include "state.h"
#include "chamber.h"

using std::string;

class Player;
class Tile;
// class Chamber;
class Item;

class Floor {
        // TODO: add these fields to UML
        const int width = 79;
        const int height = 25;
        std::shared_ptr<Player> pc;
        std::vector<std::vector<Tile *>> theFloor;
        std::vector<std::unique_ptr<Chamber>> chambers;
        State stairs;

        string floorMap;
/*
        const string defaultMap = 
            "|-----------------------------------------------------------------------------|"
            "|                                                                             |"
            "| |--------------------------|        |-----------------------|               |"
            "| |..........................|        |.......................|               |"
            "| |..........................+########+.......................|-------|       |"
            "| |..........................|   #    |...............................|--|    |"
            "| |..........................|   #    |..................................|--| |"
            "| |----------+---------------|   #    |----+----------------|...............| |"
            "|            #                 #############                |...............| |"
            "|            #                 #     |-----+------|         |...............| |"
            "|            #                 #     |............|         |...............| |"
            "|            ###################     |............|   ######+...............| |"
            "|            #                 #     |............|   #     |...............| |"
            "|            #                 #     |-----+------|   #     |--------+------| |"
            "|  |---------+-----------|     #           #          #              #        |"
            "|  |.....................|     #           #          #         |----+------| |"
            "|  |.....................|     ########################         |...........| |"
            "|  |.....................|     #           #                    |...........| |"
            "|  |.....................|     #    |------+--------------------|...........| |"
            "|  |.....................|     #    |.......................................| |"
            "|  |.....................+##########+.......................................| |"
            "|  |.....................|          |.......................................| |"
            "|  |---------------------|          |---------------------------------------| |"
            "|                                                                             |"
            "|-----------------------------------------------------------------------------|";

        string numMap = 
            "|-----------------------------------------------------------------------------|"
            "|                                                                             |"
            "| |--------------------------|        |-----------------------|               |"
            "| |11111111111111111111111111|        |22222222222222222222222|               |"
            "| |11111111111111111111111111+########+22222222222222222222222|-------|       |"
            "| |11111111111111111111111111|   #    |2222222222222222222222222222222|--|    |"
            "| |11111111111111111111111111|   #    |2222222222222222222222222222222222|--| |"
            "| |----------+---------------|   #    |----+----------------|222222222222222| |"
            "|            #                 #############                |222222222222222| |"
            "|            #                 #     |-----+------|         |222222222222222| |"
            "|            #                 #     |333333333333|         |222222222222222| |"
            "|            ###################     |333333333333|   ######+222222222222222| |"
            "|            #                 #     |333333333333|   #     |222222222222222| |"
            "|            #                 #     |-----+------|   #     |--------+------| |"
            "|  |---------+-----------|     #           #          #              #        |"
            "|  |444444444444444444444|     #           #          #         |----+------| |"
            "|  |444444444444444444444|     ########################         |55555555555| |"
            "|  |444444444444444444444|     #           #                    |55555555555| |"
            "|  |444444444444444444444|     #    |------+--------------------|55555555555| |"
            "|  |444444444444444444444|     #    |555555555555555555555555555555555555555| |"
            "|  |444444444444444444444+##########+555555555555555555555555555555555555555| |"
            "|  |444444444444444444444|          |555555555555555555555555555555555555555| |"
            "|  |---------------------|          |---------------------------------------| |"
            "|                                                                             |"
            "|-----------------------------------------------------------------------------|";
*/
        void spawnCoords();
        void setChambers(string map);

        const int floorNum;

        void spawn();
        void layout(string map);

    public:
        // ctors
        Floor(std::shared_ptr<Player> pc, string numMap, string floorMap, bool hasLayout, int floorNum);

        void updateFloor(string action);
        void init(string map, bool hasLayout);
        void generateBarrierSuit();
        void print(string action);
        bool isValidMove(State &newPos);
        bool isValidMove(int strIdxNum);
        int validPlayerTile(State &newPos);
        
        int getNumChambers();
        int getChamberSize(int chamberIdx);
        int getStringIdx(int chamberIdx, int arrIdx);

        Tile *getTile(int strIdxNum); // STRING index num
        Tile *getTile(State pos); // get tile given a State
        State getState(State &curPos, Direction dir);
        Item *getItem(State &itemPos);
        void removeItem(State pos); 
        int rNeighbourStrIdx(int strIdx, Floor &floor);
        int rNeighbourStrIdx(int strIdx);
        State idxToPos(int strIdx);
        
        bool onStairs(); 
};

#endif
