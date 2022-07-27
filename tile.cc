#include "tile.h"
#include "item.h"
#include "consumable.h"
#include "enemy.h"
#include "state.h"
#include "compass.h"
#include <iostream>
#include <memory>

using namespace std;

Tile::Tile(int x, int y, TileType type) : pos{make_unique<State>(State{x, y})}, type{type}, item{nullptr}, enemy{nullptr} {}

Tile::~Tile() {}

void Tile::removeEntities() {
    if (hasEnemy()) {
        if (enemy->hasCompass()) {
            item = make_unique<Compass>();
        } else if (enemy->dropsMerchantHorde()) {
            item = make_unique<Consumable>(ItemType::MerchantHorde);
        }
        enemy.reset(nullptr);
        return;
    }
    item.reset(nullptr); // deletes item and sets item to nullptr
    enemy.reset(nullptr); // delete enemy
}

void Tile::setId(TileType type) {
    this->type = type;
}

TileType Tile::getType() {
    return type;
}

bool Tile::hasGold() {
    if (hasItem()) {
        return item->isGold();
    }
    return false;
}

bool Tile::hasEnemy() {
    return (type == TileType::MoveableTile) && (enemy.get() != nullptr);
}

bool Tile::hasItem() {
    return (type == TileType::MoveableTile) && (item.get() != nullptr);
}

unique_ptr<Enemy> &Tile::getEnemy() {
    return enemy;
}

unique_ptr<Item> &Tile::getItem() {
    return item;
}

State Tile::getState() {
    return *pos;
}

void Tile::moveEnemy(unique_ptr<Enemy> &other) {
    // what is currently at enemy is deleted
    // but it should be okay since enemy should b nullptr
    enemy = move(other);
    // other.enemy is set to nullptr
}

void Tile::moveItem(unique_ptr<Item> &other) {
    item = move(other);
}

std::ostream &operator<<(std::ostream &out, const Tile &td) {
    TileType cur = td.type;
    switch (cur) {
        case TileType::Empty:
            out << ' ';
            break;
        case TileType::VWall:
            out << "\033[47m" <<'|' << "\033[0m";
            break;
        case TileType::HWall:
            out << "\033[47m" <<'-' << "\033[0m";
            break;
        case TileType::Passage:
            out << '#';
            break;
        case TileType::Door:
            out << '+';
            break;
         case TileType::MoveableTile:
            if (td.item.get() == nullptr && td.enemy.get() == nullptr) {
                out << '.';
            } else if (td.item.get() == nullptr) {
                if (td.enemy->hasCompass()) {
                    out << "\033[32m" << td.enemy->getChar() << "\033[0m";
                    break;
                }
                if (!td.enemy->isHostile()) {
                    out << "\033[31m" << td.enemy->getChar() << "\033[0m";
                } else { // hostile enemies
                    out << "\033[31;1m" << td.enemy->getChar() << "\033[0m";
                }
            } else {
                char item = td.item->getChar();
                if (item == 'G') {
                    out << "\033[33m" << item << "\033[0m";
                } else if (item == 'P') {
                    out << "\033[35m" << item << "\033[0m";
                } else {
                    out << "\033[32m" << item << "\033[0m"; // barrier suit, compass
                }
            }
            break;
    }
    return out;
}
