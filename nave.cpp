#include "nave.h"
#include <allegro.h>
#include<iostream>

Nave::Nave(int x, int y, int width, int height, char* img_path): Element(x, y, width, height, img_path){
    destroy = false;
    explotando = false;
}

void Nave::update(){
    if(explotando){
        cont++;
        if(cont % 3){
            index_animacion++;
        }
            std::cout << index_animacion << std::endl;
        if(index_animacion > 6){
            explotando = false;
            if(cantidad_vidas <= 0)
                destroy = true;
        }
    }
}

void Nave::render(BITMAP *buffer){
    if(!destroy){
        int tile;

        if(!explotando)
            tile = 0;
        else
            tile = ((index_animacion % 2) + 1) * width;


        masked_blit(img, buffer, tile, 0, x, y, width, height);
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
    explotando = true;
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
