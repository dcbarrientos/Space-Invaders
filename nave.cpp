#include "nave.h"
#include <allegro.h>

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

        if(index_animacion > 8){
            index_animacion = 0;
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

bool Nave::is_explotando(){
    return explotando;
}

void Nave::set_position(int _x, int _y){
    x = _x;
    y = _y;
}

int Nave::get_cantidad_vidas(){
    return cantidad_vidas;
}

bool Nave::colision(Element *e){
    if(e->get_x() < x || e->get_y() > y)
        return false;
    else{
        if(e->get_y() + e->get_height() < y)
            return false;
    }

    return true;
}
