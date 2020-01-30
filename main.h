#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <allegro.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define BORDE 40

#define PLAYING_STATE 0
#define MENU_STATE 1
#define LOADING_STATE 2
#define OVER_STATE 3

#define ENEMIGO_WIDTH 25
#define ENEMIGO_HEIGHT 20
#define ENEMIGOS_COLUMNA 5
#define ENEMIGOS_FILA 11

#define NAVE_WIDTH 30
#define NAVE_HEIGHT 20
#define BALA_WIDTH 6
#define BALA_HEIGHT 12

#define BALA_SPEED 8
#define BALA_ENEMIGO_WIDTH 12
#define BALA_ENEMIGO_HEIGHT 12
#define BALA_ENEMIGO_ESPERA 30

#define MAX_DISPAROS 4

void init_allegro(int ancho, int alto);
bool init_audio(int vol_derecha, int vol_izquierda);
void render(BITMAP *buffer);
void load_level();
void update();
void disparar_enemigo(int n_enemigo);
bool is_cambio_direccion();
int get_fila_enemigo_centrada(int cantidad_enemigos, int ancho_enemigo);
void crear_bunker(int _x, int _y);
void print_bar(BITMAP *buffer);
#endif // MAIN_H_INCLUDED
