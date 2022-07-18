#ifndef TILE_H
#define TILE_H

#include <memory>

class Enemy;
class Item;

// TILE IDENTIFIERS:
// 0 - empty space ( )
// 1 - vertical wall (-)
// 2 - horizental wall (|)
// 3 - passage (#)
// 4 - door (+)
// 5 - moveable tile (nothing currently on it)

// Since tiles "own" the enemy and item, tiles must be responsible for freeing the item / enemy after they die
class Tile {
    int x;
    int y;
    int id;
    std::unique_ptr<Item> item;
    std::unique_ptr<Enemy> enemy;
    public:
    Tile(int x, int y, int id);
    void removeEntities(); // frees the *item AND *enemy. Set tile id back to 0.
};

class Tile {

        int id = 0; // 0 should mean empty tile

    public:
        void setId(int newId);
        friend std::ostream &operator<<(std::ostream &out, const Tile &td);

};

#endif
