#ifndef BALA_H_INCLUDED
#define BALA_H_INCLUDED

#include "element.h"
#include "main.h"

class Bala: public Element{
private:
    int speed;
public:
    Bala(int x, int y, int width, int height, int _speed, char *img_path): Element(x, y, width, height, img_path), speed(_speed){};
    ~Bala();
    void update();
    bool is_out();
    bool colision(Element *e);
};

#endif // BALA_H_INCLUDED
