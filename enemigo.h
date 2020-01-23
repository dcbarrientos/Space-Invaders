#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED

#include "element.h"

#define ESPERA_ENEMIGO_MAX 30
#define X_STEP 20
#define Y_STEP 20

class Enemigo: public Element{
private:
    int tipo;
    int img_actual;
    int tiempo_espera_animacion;
    int screen_width;
    int speed;

public:
    Enemigo(int _x, int _y, int _width, int _height, int _tipo, char *img_path);
    void update();
    void render(BITMAP *buffer);
    void cambiar_rumbo();
    bool is_borde(int _width);
};

#endif // ENEMIGO_H_INCLUDED
