#include <iostream>
#include <vector>

#include "main.h"
#include "nave.h"
#include "bala.h"
#include "enemigo.h"
#include "math.h"
#include "menu.h"
#include "bunker.h"

using namespace std;

Nave *nave;
Bala *bala_player;
vector<Bala*> balas_enemigos;
vector<Enemigo*> enemigos;
vector<Bunker*> bunkers;

int cont; //Tiempo espera entre tiros de los enemigos.
int game_state;
Menu *menu;
Menu *menu2;
BITMAP *fondo;
int pausa_cargando = 0;
int score;
int hi_score;
FONT *fuente;

//https://www.youtube.com/watch?v=YwMXIBB_JfQ&list=PL6hPvfzEEMDZ4PSkN-5Zj_0-YVO7b0OgC&index=12
int main(int argc, char *argv[]){
    init_allegro(SCREEN_WIDTH, SCREEN_HEIGHT);
    //init_audio(70, 70);

    PALETTE palette;
    fuente = load_font("resources\\fonts\\pixelcoleco.pcx", palette, NULL);
    if(!fuente){
        cout << "No cargó la fuente" << endl;
        return -1;
    }

    BITMAP *buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);

    srand(time(NULL));

    char nave_path[] = "resources\\nave.bmp";
    char bala_path[] = "resources\\bala2.bmp";
    char fondo_path[] = "resources\\fondo.bmp";
    char menu_path[] = "resources\\portada.bmp";

    fondo = load_bitmap(fondo_path, NULL);

    int x = SCREEN_WIDTH / 2;
    int y = SCREEN_HEIGHT - 80;
    cont = 0;

    balas_enemigos.clear();

    menu = new Menu(menu_path);

    nave = new Nave(x, y, NAVE_WIDTH, NAVE_HEIGHT, nave_path);

    game_state = MENU_STATE;
    hi_score = 0;
    while(!key[KEY_ESC] ){
        clear_to_color(buffer, 0x000000);

        if(game_state == PLAYING_STATE){
            if(nave->is_alive()){
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

                if(enemigos.size() > 0)
                    disparar_enemigo(rand() % enemigos.size());
            }
        }else if(game_state == MENU_STATE){
            if(key[KEY_ENTER]){
                game_state = LOADING_STATE;
                menu->set_fila(1);
                pausa_cargando = 0;
                nave->set_cantidad_vidas(MAX_VIDAS);
                load_level();
                nave->set_position(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 80);
                score = 0;
            }
        }else if(game_state == OVER_STATE){
            if(key[KEY_SPACE]){

                game_state = MENU_STATE;
                menu->set_fila(0);
            }

        }

        update();
        render(buffer);

        rest(1000/60);  //Actualizo 60 veces por segundo.
    }

    delete(nave);
    delete(menu);

    return 0;
}

void load_level(){
    //Posiciono los enemigos
    int xt = get_fila_enemigo_centrada(ENEMIGOS_FILA, ENEMIGO_WIDTH);
    int yt = 160;
    int stepx = 25;
    int stepy = 20;
    char enemigos_path[] = "resources\\enemigos.bmp";
    enemigos.clear();

    for(int fila = 0; fila < ENEMIGOS_FILA; fila++){
        for(int columna = 0; columna < ENEMIGOS_COLUMNA; columna++){
            enemigos.insert(enemigos.end(), new Enemigo(xt + fila * stepx, yt + columna * stepy, ENEMIGO_WIDTH, ENEMIGO_HEIGHT, (int)(columna / 2), enemigos_path));
        }
    }

    //Posiciono los bunkers
    bunkers.clear();
    crear_bunker(64, 470);
    crear_bunker(188, 470);
    crear_bunker(311, 470);
    crear_bunker(434, 470);
}

int get_fila_enemigo_centrada(int cantidad_enemigos, int ancho_enemigo){
    int _x = (WIDTH - cantidad_enemigos * ancho_enemigo) / 2;

    return _x;
}

void update(){
    if(game_state == PLAYING_STATE){
        if(nave->is_explotando())
            nave->update();

        //actualizo la posicion de las balas de los enemigos
        for(unsigned int i = 0; i < balas_enemigos.size(); i++)
            balas_enemigos[i]->update();

        for(unsigned int i = 0; i < bunkers.size(); i++)
            bunkers[i]->update();

        //verifico si las balas de los enemigos salieron de pantalla y las elimino
        for(unsigned int i = 0; i < balas_enemigos.size(); i++){
            if(balas_enemigos[i]->is_out()){
                delete(balas_enemigos[i]);
                balas_enemigos.erase(balas_enemigos.begin() + i);
            }
        }

        //Verifico si las balas de los enemigos colisionan con la nave
        for(unsigned int i = 0; i < balas_enemigos.size(); i++){
            if(balas_enemigos[i]->colision(nave)){
                delete(balas_enemigos[i]);
                balas_enemigos.erase(balas_enemigos.begin() + i);
                nave->hit();
            }
        }

        //Actualizo la bala del jugador y verifico si salio de pantalla para eliminarla
        if(bala_player != NULL){
            bala_player->update();

            if(bala_player->is_out()){
                delete(bala_player);
                bala_player = NULL;
            }
        }

        //Verifico si los enemigos llegaron al final de la pantalla para cambiar de rumbo
        if(is_cambio_direccion()){
            for(unsigned int i = 0; i < enemigos.size(); i++)
                enemigos[i]->cambiar_rumbo();
        }

        //Actualizo la posicion de los enemigos.
        for(unsigned int i = 0; i < enemigos.size(); i++){
            enemigos[i]->update();
        }

        //Verificar colisiones

        //elimino enemigos que estan en condiciones de ser eliminados.
        for(unsigned int i = 0; i < enemigos.size(); i++){
            if(enemigos[i]->get_destroy()){
                delete(enemigos[i]);
                enemigos.erase(enemigos.begin() + i);
            }
        }

        //elimino bunkers que estan en condiciones de ser eliminados.
        for(unsigned int i = 0; i < bunkers.size(); i++){
            if(bunkers[i]->get_destroy()){
                delete(bunkers[i]);
                bunkers.erase(bunkers.begin() + i);
            }
        }

        //Verifico la colision entre la bala de los enemigos y los bunkers
        for(unsigned int ba = 0; ba < balas_enemigos.size(); ba++){
            for(unsigned int bu = 0; bu < bunkers.size(); bu++){
                if(balas_enemigos[ba]->colision(bunkers[bu])){
                    bunkers[bu]->set_hit();
                    delete(balas_enemigos[ba]);
                    balas_enemigos.erase(balas_enemigos.begin() + ba);
                }
            }
        }

        //Verifico la colision entre la bala del jugador y los enemigos
        if(bala_player != NULL){
            for(unsigned int i = 0; i < enemigos.size(); i++){
                if(bala_player->colision(enemigos[i])){
                    enemigos[i]->set_hit(true);
                    score += enemigos[i]->get_score();
                    delete(bala_player);
                    bala_player = NULL;
                    break;
                }
            }
        }

        //Verifico la colision entre la bala del jugador y la de los enemigos.
        if(bala_player != NULL){
            for(unsigned int i = 0; i < balas_enemigos.size() && bala_player != NULL; i++){
                if(balas_enemigos[i]->colision(bala_player)){
                    delete(balas_enemigos[i]);
                    balas_enemigos.erase(balas_enemigos.begin() + i);
                    delete(bala_player);
                    bala_player = NULL;
                }
            }
        }

        //Verifico la colision entre la bala del jugador y los bunkers
        if(bala_player != NULL){
            for(unsigned int i = 0; i < bunkers.size() && bala_player != NULL; i++){
                if(bala_player->colision(bunkers[i])){
                    bunkers[i]->set_hit();
                    delete(bala_player);
                    bala_player = NULL;
                }
            }
        }

        //Verifico si los enemigos llegan a la nave
        for(unsigned int i = 0; i < enemigos.size(); i++){
            if(nave->colision(enemigos[i])){
                nave->hit();
                nave->set_cantidad_vidas(0);
            }
        }

        if(!nave->is_alive()){
            game_state = OVER_STATE;
            if(score > hi_score)
                hi_score = score;

            for(unsigned i = 0; i < enemigos.size(); i++){
                enemigos[i]->set_speed(0);
            }
        }
    }else if(game_state == MENU_STATE){
        menu->update();
    }else if(game_state == LOADING_STATE){
        menu->update();
        pausa_cargando++;
        if(pausa_cargando > 100)
            game_state = PLAYING_STATE;
    }else if(game_state == OVER_STATE){
        nave->update();

        for(unsigned i = 0; i < enemigos.size(); i++){
            enemigos[i]->update();
        }

    }
}

void render(BITMAP *buffer){
    if(game_state == PLAYING_STATE || game_state == OVER_STATE){
        if(nave != NULL)
            nave->render(buffer);

        if(bala_player != NULL)
            bala_player->render(buffer);

        for(unsigned int i = 0; i < balas_enemigos.size(); i++)
            balas_enemigos[i]->render(buffer);

        if(enemigos.size() > 0){
            for(unsigned int i = 0; i < enemigos.size(); i++)
                enemigos[i]->render(buffer);
        }

        if(bunkers.size() > 0){
            for(unsigned int i = 0; i < bunkers.size(); i++)
                bunkers[i]->render(buffer);
        }
        print_bar(buffer);
    } else if(game_state == MENU_STATE || game_state == LOADING_STATE){
        menu->render(buffer);
    }

    masked_blit(fondo, buffer, 0, 0, 0, 0, 600, 600);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void print_bar(BITMAP *buffer){
    int _y = 130;
    int _x = 60;

    string t = "Score: " + to_string(score);
    textout_ex(buffer, fuente, t.c_str(), _x, _y, 0xffffff, 0x000000);

    t = "Lives: " + to_string(nave->get_cantidad_vidas());
    textout_ex(buffer, fuente, t.c_str(), _x + 300, _y, 0xffffff, 0x000000);

    t = "HI-SCORE: " + to_string(hi_score);
    textout_ex(buffer, fuente, t.c_str(), _x + 150, _y, 0xffffff, 0x000000);
}

void crear_bunker(int _x, int _y){
    char bunker_path[] = "resources\\escudos.bmp";

    bunkers.insert(bunkers.end(), new Bunker(_x + 00, _y, 20, 16, 0, bunker_path));
    bunkers.insert(bunkers.end(), new Bunker(_x + 20, _y, 20, 16, 4, bunker_path));
    bunkers.insert(bunkers.end(), new Bunker(_x + 40, _y, 20, 16, 2, bunker_path));

    bunkers.insert(bunkers.end(), new Bunker(_x + 00, _y + 16, 20, 16, 1, bunker_path));
    bunkers.insert(bunkers.end(), new Bunker(_x + 40, _y + 16, 20, 16, 3, bunker_path));
}

bool is_cambio_direccion(){
    for(unsigned int i = 0; i < enemigos.size(); i++){
        if(enemigos[i]->is_borde())
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
