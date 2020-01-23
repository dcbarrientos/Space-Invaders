#include "nave.h"


void Nave::update(int key){
}

void Nave::move(int key){
    if(key == KEY_LEFT)
        x -= X_SPEED;
    if(key == KEY_RIGHT)
        x += X_SPEED;
}
