#include "enemigo.h"
#include <iostream>

Enemigo::Enemigo(int _x, int _y, int _width, int _height, int _tipo, char *img_path): Element(_x, _y, _width, _height, img_path){
    tipo = _tipo;
    img_actual = 0;
    tiempo_espera_animacion = 0;
    speed = X_STEP;
    destroy = false;

    img_explosion = load_bitmap( "resources\\pum_enemigo.bmp", NULL);
 }

Enemigo::~Enemigo(){
}

void Enemigo::update(){
    tiempo_espera_animacion++;
    if(tiempo_espera_animacion >= ESPERA_ENEMIGO_MAX){
        tiempo_espera_animacion = 0;
        if(img_actual == 0)
            img_actual = 1;
        else
            img_actual = 0;
        x += speed;

    }
}

void Enemigo::render(BITMAP *buffer){
    int xpos = img_actual * width;
    int ypos = tipo * height;
    if(hit){
        destroy = true;
        masked_blit(img_explosion, buffer, 0, 0, x, y, width, height);
    }else
        masked_blit(img, buffer, xpos, ypos, x, y, width, height);

}

void Enemigo::cambiar_rumbo(){
    speed *= -1;
    x += speed;
    y += Y_STEP;
}

bool Enemigo::is_borde(int screen_width){
    int borde = 5;
    if(speed > 0){
        if(x + width >= screen_width - borde)
            return true;
    }else{
        if(x - borde < 0)
            return true;
    }
    return false;
}
