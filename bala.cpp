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


