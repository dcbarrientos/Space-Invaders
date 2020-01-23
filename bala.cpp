#include <iostream>
#include "main.h"
#include "bala.h"

Bala::~Bala(){

}

void Bala::update(){
    y += speed;
}

bool Bala::is_out(){
    if(speed < 0){
        if((y + height) < 0)
            return true;
    }else{
        if((y - height > SCREEN_HEIGHT))
            return true;
    }

    return false;
}

bool Bala::colision(Element *e){
    if(!e->get_hit()){
        if((x + width) < e->get_x() || x > (e->get_x() + e->get_width())){
            return false;
        } else {
            if((y + height) < e->get_y() || y > (e->get_y() + e->get_height()))
                return false;
            else
                return true;
        }
    }
    return false;
}


