#ifndef NAVE_H_INCLUDED
#define NAVE_H_INCLUDED

#include "element.h"


#define X_SPEED 5
#define MAX_VIDAS 3

class Nave: public Element{
    int cantidad_vidas;
    int index_animacion;
    bool destroy;
    int cont;
    bool explotando;

public:
    Nave(int x, int y, int width, int height, char* img_path);
    void move(int key);
    void update();
    void render(BITMAP *buffer);
    void hit();
    void set_cantidad_vidas(int _cantidad_vidas);
    bool is_alive();
    bool get_destroy();
    void set_position(int _x, int _y);
};

#endif // NAVE_H_INCLUDED
