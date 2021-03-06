#include "enemigo.h"
#include<iostream>
Enemigo::Enemigo(int _x, int _y, int _width, int _height, int _tipo, int _fila, char *img_path): Element(_x, _y, _width, _height, img_path){
    tipo = _tipo;
    img_actual = 0;
    tiempo_espera_animacion = 0;
    speed = X_STEP;
    destroy = false;
    tiempo_espera = ESPERA_ENEMIGO_MAX;
    img_explosion = load_bitmap( "resources\\pum_enemigo.bmp", NULL);
    fila = _fila;
 }

Enemigo::~Enemigo(){
}

void Enemigo::update(){
    tiempo_espera_animacion++;

    if(tiempo_espera_animacion >= tiempo_espera){
        tiempo_espera_animacion = 0;
        if(img_actual == 0)
            img_actual = 1;
        else
            img_actual = 0;

        x += speed;

        if(hit)
            destroy = true;

    }
}

void Enemigo::render(BITMAP *buffer){
    int xpos = img_actual * width;
    int ypos = tipo * height;
    if(hit){
        //destroy = true;
        masked_blit(img_explosion, buffer, 0, 0, x - 10, y - 5, 41, 34);
    }else
        masked_blit(img, buffer, xpos, ypos, x, y, width, height);

}

void Enemigo::cambiar_rumbo(){
    speed *= -1;
    tiempo_espera *= .8;

    //x += speed;
    y += Y_STEP;
}

bool Enemigo::is_borde(){
    //int borde = WIDTH - BORDE;
    if(speed > 0){
        //std::cout << x + width << std::endl;
        if(x + width >= (SCREEN_WIDTH - BORDE - 10))
            return true;
    }else{
        if((x) < BORDE + 10)
            return true;
    }
    return false;
}

void Enemigo::set_speed(int _speed){
    speed = _speed;
}

int Enemigo::get_score(){
    if(tipo == 0)
        return 30;
    else if(tipo == 1)
        return 20;
    else if(tipo == 2)
        return 10;

    return 100;
}

