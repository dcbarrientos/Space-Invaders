#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED

#include "element.h"
#include "main.h"

#define ESPERA_ENEMIGO_MAX 30
#define X_STEP 5
#define Y_STEP 10

class Enemigo: public Element{
private:
    int tipo;
    int img_actual;
    int tiempo_espera;
    int tiempo_espera_animacion;
    int screen_width;
    int fila;
    int speed;
    BITMAP *img_explosion;

public:
    Enemigo(int _x, int _y, int _width, int _height, int _tipo, int _fila, char *img_path);
    ~Enemigo();
    void update();
    void render(BITMAP *buffer);
    void cambiar_rumbo();
    bool is_borde();
    void set_speed(int _speed);
    int get_score();
};

#endif // ENEMIGO_H_INCLUDED
