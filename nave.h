#ifndef NAVE_H_INCLUDED
#define NAVE_H_INCLUDED

#include "element.h"


#define X_SPEED 5

class Nave: public Element{
    public:
    Nave(int x, int y, int width, int height, char* img_path): Element(x, y, width, height, img_path){};
    void move(int key);
    void update(int key);
};

#endif // NAVE_H_INCLUDED
