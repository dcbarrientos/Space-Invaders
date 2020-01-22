#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define WIDTH 600
#define HEIGHT 375

#define NAVE_WIDTH 30
#define NAVE_HEIGHT 20

#define MAX_DISPAROS 4

void init_allegro(int ancho, int alto);
bool init_audio(int vol_derecha, int vol_izquierda);
void render(BITMAP *buffer);
void update();
#endif // MAIN_H_INCLUDED
