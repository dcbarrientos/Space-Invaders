#include "nave.h"
/*
void Nave::render(BITMAP *buffer){
    masked_blit(img, buffer, 0, 0, x, y, NAVE_WIDTH, NAVE_HEIGHT);
}
*/
void Nave::update(int key){
}

void Nave::move(int key){
    if(key == KEY_LEFT)
        x -= X_SPEED;
    if(key == KEY_RIGHT)
        x += X_SPEED;
}
