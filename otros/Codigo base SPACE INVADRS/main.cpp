#include <allegro.h>
#include "inicia.h"
#include "disparos.h"

#define ANCHO 600
#define ALTO  375


int main(){

    inicia_allegro(ANCHO,ALTO); // fuciones del include inicia.h
	inicia_audio(70,70);        //

    BITMAP *buffer = create_bitmap(ANCHO, ALTO);;
    BITMAP *bala = load_bitmap("Recursos/Bala2.bmp", NULL);
    BITMAP *nave = load_bitmap("Recursos/nave.bmp", NULL);




	return 0;
}
END_OF_MAIN();

