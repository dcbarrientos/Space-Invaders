#include "nave.h"
#include <allegro.h>
#include <iostream>

Nave::Nave(int x, int y, int width, int height, char* img_path): Element(x, y, width, height, img_path){
    destroy = false;
}

void Nave::update(){
    if(cantidad_vidas <= 0){
        cont++;
        if(cont % 3)
            index_animacion++;

        if(index_animacion > 2)
            destroy = true;
    }
}

void Nave::render(BITMAP *buffer){
    if(!destroy){
        masked_blit(img, buffer, index_animacion * width, 0, x, y, width, height);
    }
}

void Nave::move(int key){
    if(key == KEY_LEFT)
        x -= X_SPEED;
    if(key == KEY_RIGHT)
        x += X_SPEED;
}

void Nave::hit(){
    cantidad_vidas--;
}

void Nave::set_cantidad_vidas(int _cantidad_vidas){
    cantidad_vidas = _cantidad_vidas;
    destroy = false;
    index_animacion = 0;
}

bool Nave::is_alive(){
    if(cantidad_vidas > 0)
        return true;

    return false;
}

bool Nave::get_destroy(){
    return destroy;
}

void Nave::set_position(int _x, int _y){
    x = _x;
    y = _y;
}
