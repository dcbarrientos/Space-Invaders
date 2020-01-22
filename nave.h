#ifndef NAVE_H_INCLUDED
#define NAVE_H_INCLUDED

#include <string>
#include "element.h"

class Nave: public Element{
    public:
    Nave(int x, int y, std::string img_path): Element(x, y, img_path){};
    void update();
    void render(BITMAP buffer);
};

#endif // NAVE_H_INCLUDED
