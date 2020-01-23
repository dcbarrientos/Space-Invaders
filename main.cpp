#include <iostream>
#include <vector>

#include "main.h"
#include "nave.h"
#include "bala.h"
#include "enemigo.h"
#include "math.h"

using namespace std;
Nave *nave;
Bala *bala_player;
vector<Bala*> balas_enemigos;
vector<Enemigo*> enemigos;
int cont; //Tiempo espera entre tiros de los enemigos.

//https://www.youtube.com/watch?v=a2MoETBfdQE&list=PL6hPvfzEEMDZ4PSkN-5Zj_0-YVO7b0OgC&index=3
int main(int argc, char *argv[]){
    init_allegro(SCREEN_WIDTH, SCREEN_HEIGHT);
    //init_audio(70, 70);

    BITMAP *buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);

    srand(time(NULL));

    char nave_path[] = "resources\\nave.bmp";
    char bala_path[] = "resources\\bala2.bmp";

    int x = SCREEN_WIDTH / 2;
    int y = SCREEN_HEIGHT - 50;
    cont = 0;

    balas_enemigos.clear();

    nave = new Nave(x, y, NAVE_WIDTH, NAVE_HEIGHT, nave_path);
    load_level();
    while(!key[KEY_ESC]){
        clear_to_color(buffer, 0x000000);

        if(key[KEY_LEFT])
            nave->move(KEY_LEFT);
        if(key[KEY_RIGHT])
            nave->move(KEY_RIGHT);

        if(key[KEY_SPACE]){
            if(bala_player == NULL){
                int xt = nave->get_x() + NAVE_WIDTH / 2 - BALA_WIDTH / 2;
                bala_player = new Bala(xt, nave->get_y(), BALA_WIDTH, BALA_HEIGHT, BALA_SPEED * -1,bala_path);
            }
        }
        disparar_enemigo(rand() % enemigos.size());

        update();
        render(buffer);

        rest(1000/60);  //Actualizo 60 veces por segundo.
    }

    delete(nave);

    return 0;
}

void load_level(){
    int xt = 50;
    int yt = 80;
    int stepx = 25;
    int stepy = 20;
    char enemigos_path[] = "resources\\enemigos.bmp";

    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 5; j++){
            enemigos.insert(enemigos.end(), new Enemigo(xt + i * stepx, yt + j * stepy, 25, 20, (int)(j / 2), enemigos_path));
        }
    }
}

void update(){
    for(unsigned int i = 0; i < balas_enemigos.size(); i++)
        balas_enemigos[i]->update();

    for(unsigned int i = 0; i < balas_enemigos.size(); i++){
        if(balas_enemigos[i]->is_out()){
            delete(balas_enemigos[i]);
            balas_enemigos.erase(balas_enemigos.begin() + i);
        }
    }

    if(bala_player != NULL){
        bala_player->update();

        if(bala_player->is_out()){
            delete(bala_player);
            bala_player = NULL;
        }
    }

    if(is_cambio_direccion()){
        for(unsigned int i = 0; i < enemigos.size(); i++)
            enemigos[i]->cambiar_rumbo();
    }

    for(unsigned int i = 0; i < enemigos.size(); i++){
        enemigos[i]->update();
    }


    //Verificar colisiones
}

void render(BITMAP *buffer){
    nave->render(buffer);
    if(bala_player != NULL)
        bala_player->render(buffer);

    for(unsigned int i = 0; i < balas_enemigos.size(); i++)
        balas_enemigos[i]->render(buffer);

    for(unsigned int i = 0; i < enemigos.size(); i++)
        enemigos[i]->render(buffer);

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

bool is_cambio_direccion(){
    for(unsigned int i = 0; i < enemigos.size(); i++){
        if(enemigos[i]->is_borde(SCREEN_WIDTH))
            return true;
    }
    return false;
}

//Funcion que hace que un enemigo dispare.
void disparar_enemigo(int n_enemigo){
    if(cont++ == BALA_ENEMIGO_ESPERA){
        cont = 0;
        char bala_enemigo_path[] = "resources\\Bala_enem.bmp";

        int xt = enemigos[n_enemigo]->get_x() + BALA_ENEMIGO_WIDTH / 2;
        balas_enemigos.insert(balas_enemigos.end(), new Bala(xt, enemigos[n_enemigo]->get_y(), BALA_ENEMIGO_WIDTH, BALA_ENEMIGO_HEIGHT, BALA_SPEED, bala_enemigo_path));
    }
}

void init_allegro(int ancho, int alto){
    allegro_init();
    install_keyboard();

    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, ancho, alto, 0, 0);
}

bool init_audio(int vol_derecha, int vol_izquierda){
    if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0){
        allegro_message("Error: no se pudo inicializar el sonido\n%s\n", allegro_error);
        return false;
    }

    set_volume(vol_izquierda, vol_derecha);
    return true;
}

END_OF_MAIN()
