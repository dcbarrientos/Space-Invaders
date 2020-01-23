#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define WIDTH 600
#define HEIGHT 375

#define NAVE_WIDTH 30
#define NAVE_HEIGHT 20
#define BALA_WIDTH 6
#define BALA_HEIGHT 12

#define BALA_SPEED 8
#define BALA_ENEMIGO_WIDTH 12
#define BALA_ENEMIGO_HEIGHT 12
#define BALA_ENEMIGO_ESPERA 20


#define MAX_DISPAROS 4

void init_allegro(int ancho, int alto);
bool init_audio(int vol_derecha, int vol_izquierda);
void render(BITMAP *buffer);
void update();
void disparar_enemigo();
#endif // MAIN_H_INCLUDED
