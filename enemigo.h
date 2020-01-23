#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED

#include "element.h"

class Enemigo: public Element{
public:
    Enemigo(int _x, int _y, int _width, int _height, int _speed, char *img_path):Element(_x, _y, _width, _height, img_path){};
    void update();
};

#endif // ENEMIGO_H_INCLUDED
