#include "character.h"
#include "info.h"
#include "state.h"
#include <cmath>

Info Character::getInfo() {
    return *stats;
}

void Character::setHp(int newHp) {
    stats->hp = newHp;
}
void Character::setAtk(int newAtk) {
    stats->atk = newAtk;
}
void Character::setDef(int newDef) {
    stats->def = newDef;
}
void Character::setGold(int newGold) {
    stats->gold = newGold;
}

State Character::getState() {
    return *pos;
}

void Character::setState(State newPos) {
    *pos = newPos;
}

void Character::toggleMove() {
    hasMoved = !hasMoved;
}

bool Character::isDead() {
    return getInfo().hp == 0;
}

void Character::attack(Character &victim) {
    int damage = ceil((100 / (100 + victim.getInfo().def)) * getInfo().atk);
    victim.getAttacked(damage);
    // enemies take damage normally
    // players have to check if they have barrier suit + 50% miss rate
}

bool Character::move(Direction dir) {
    return false;
}