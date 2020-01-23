#include <iostream>
#include "bala.h"

Bala::~Bala(){
    std::cout << "elimino bala" << std::endl;
}

void Bala::update(){
    y += speed;
}

bool Bala::is_out(){
    if(speed < 0){
        if((y + height) < 0)
            return true;
    }else{
        if((y - height > height))
            return true;
    }

    return false;
}


