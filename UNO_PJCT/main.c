
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <fmodex/fmod.h>
#include <stdlib.h>
#include <time.h>
#include "const_globls.h"
int mouse_move_click(SDL_Rect pos_Mouse, SDL_Rect posJ, SDL_Rect posI, SDL_Rect posQ);
int mouse_on_arrow(SDL_Rect pos);
void afficher_instructions(SDL_Surface* surface);
void lancer_jeu(SDL_Surface* surface, FMOD_SYSTEM *sys, FMOD_SOUND *sound1, FMOD_SOUND *sound2, FMOD_SOUND *uno);

SDL_Surface *ecran,*pointer,*hand;

int main(int argc, char* argv[]){

    /*-------------------le son-------------------*/
    FMOD_SYSTEM *system;
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
    FMOD_SOUND *sound1 = NULL, *melanger=NULL, *musique=NULL, *uno=NULL;
    FMOD_CHANNEL *channel;
    FMOD_System_CreateSound(system, "tiraa.wav", FMOD_CREATESAMPLE, 0, &sound1);
    FMOD_System_CreateSound(system, "toraa.wav", FMOD_CREATESAMPLE, 0, &melanger);
    FMOD_System_CreateSound(system, "uno.wav", FMOD_CREATESAMPLE, 0, &uno);
    FMOD_System_CreateSound(system, "musique.wav", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &musique);
    FMOD_System_GetChannel(system, 9, &channel);
    /*-------------------fin son-------------------*/


    SDL_Init(SDL_INIT_EVERYTHING);
    int cc=1, button;
    SDL_Surface *Home_BG, *joueer, *joueer_active, *instruction, *instruction_active, *quitter, *quitter_active, *instruction_img;
    SDL_Rect position_joueer, position_inst, position_quitter, mouse_move, mouse_click;
    SDL_Event e;
    /*-------------------chargement des images-------------------*/
    Home_BG=IMG_Load("img/home/home_bg.bmp");    instruction_img=IMG_Load("img/inst.bmp");
    joueer=IMG_Load("img/home/jouer.png");       joueer_active=IMG_Load("img/home/jouer_active.png");
    instruction=IMG_Load("img/home/inst.png");   instruction_active=IMG_Load("img/home/inst_active.png");
    quitter=IMG_Load("img/home/quitter.png");    quitter_active=IMG_Load("img/home/quitter_active.png");
    pointer=IMG_Load("pointer.png");             hand=IMG_Load("hand.png");
    /*-------------------fin de chargement--------------------*/

    /*-------------------position-------------------*/
    position_joueer.x=454;  position_inst.x=454; position_quitter.x=454;
    position_joueer.y=246;  position_inst.y=341; position_quitter.y=435;
    /*-------------------fin positioon-------------------*/

    SDL_putenv("SDL_VIDEO_WINDOW_POS=center");
    ecran=SDL_SetVideoMode(850, 650, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_ShowCursor(SDL_DISABLE);  //on disactive le curseur
    FMOD_Sound_SetLoopCount(musique, -1);
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0,NULL);
    while(cc){
        SDL_WaitEvent(&e);
        switch(e.type){
            case SDL_QUIT:
                cc=0;
            break;
            case SDL_MOUSEMOTION:
                mouse_move.x=e.motion.x;
                mouse_move.y=e.motion.y;
            break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT){
                    mouse_click.x= e.button.x;
                    mouse_click.y= e.button.y;
                }
            break;
        }

        SDL_BlitSurface(Home_BG, NULL, ecran, NULL);
        switch( mouse_move_click(mouse_move, position_joueer, position_inst, position_quitter) ){
            case 1:
                SDL_BlitSurface(joueer_active, NULL, ecran, &position_joueer);
                SDL_BlitSurface(instruction, NULL, ecran, &position_inst);
                SDL_BlitSurface(quitter, NULL, ecran, &position_quitter);
                SDL_BlitSurface(hand, NULL, ecran, &mouse_move);
            break;
            case 2:
                SDL_BlitSurface(joueer, NULL, ecran, &position_joueer);
                SDL_BlitSurface(instruction_active, NULL, ecran, &position_inst);
                SDL_BlitSurface(quitter, NULL, ecran, &position_quitter);
                SDL_BlitSurface(hand, NULL, ecran, &mouse_move);
            break;
            case 3:
                SDL_BlitSurface(joueer, NULL, ecran, &position_joueer);
                SDL_BlitSurface(instruction, NULL, ecran, &position_inst);
                SDL_BlitSurface(quitter_active, NULL, ecran, &position_quitter);
                SDL_BlitSurface(hand, NULL, ecran, &mouse_move);
            break;
            default:
                SDL_BlitSurface(joueer, NULL, ecran, &position_joueer);
                SDL_BlitSurface(instruction, NULL, ecran, &position_inst);
                SDL_BlitSurface(quitter, NULL, ecran, &position_quitter);
                SDL_BlitSurface(pointer, NULL, ecran, &mouse_move);
        }
        SDL_Flip(ecran);
        if( (button= mouse_move_click(mouse_click, position_joueer, position_inst, position_quitter)) ){
            mouse_click.x=0;
            switch(button){
                case 1:
                    ecran=SDL_SetVideoMode(1140, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                    lancer_jeu(ecran, system, sound1, melanger, uno);
                    ecran=SDL_SetVideoMode(850, 650, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0,NULL);
                break;
                case 2:
                     afficher_instructions(instruction_img);
                break;
                case 3:
                    cc=0;
                break;
            }
        }
    }
    SDL_FreeSurface(instruction_img);
    SDL_FreeSurface(pointer);
    SDL_FreeSurface(hand);
    SDL_FreeSurface(Home_BG);
    SDL_FreeSurface(joueer);
    SDL_FreeSurface(joueer_active);
    SDL_FreeSurface(quitter);
    SDL_FreeSurface(quitter_active);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    FMOD_Sound_Release(sound1);
    FMOD_Sound_Release(melanger);
    FMOD_Sound_Release(musique);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    SDL_Quit();
return EXIT_SUCCESS;}

int mouse_move_click(SDL_Rect pos_Mouse, SDL_Rect posJ, SDL_Rect posI, SDL_Rect posQ){
    if(pos_Mouse.x > posJ.x){
        if(pos_Mouse.x < (posJ.x + 190) && pos_Mouse.y > posJ.y && pos_Mouse.y < (posJ.y + 60) ){ return 1; }
        if(pos_Mouse.x < (posI.x + 350) && pos_Mouse.y > posI.y && pos_Mouse.y < (posI.y + 60) ){ return 2; }
        if(pos_Mouse.x < (posQ.x + 235) && pos_Mouse.y > posQ.y && pos_Mouse.y < (posQ.y + 60) ){ return 3; }
    }
    return 0;
}

void afficher_instructions(SDL_Surface* surface){
    int cc=1;
    SDL_Rect mouse_move, mouse_click;
    SDL_Event e;
    while(cc){
        SDL_WaitEvent(&e);
        switch(e.type){
            case SDL_MOUSEMOTION:
                mouse_move.x=e.motion.x;
                mouse_move.y=e.motion.y;
            break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT){
                    mouse_click.x= e.button.x;
                    mouse_click.y= e.button.y;
                }
            break;
        }
        if( mouse_on_arrow(mouse_move) ){
         SDL_BlitSurface(surface, NULL, ecran, NULL);
         SDL_BlitSurface(hand, NULL, ecran, &mouse_move);
        }else{
         SDL_BlitSurface(surface, NULL, ecran, NULL);
         SDL_BlitSurface(pointer, NULL, ecran, &mouse_move);
        }
        if( mouse_on_arrow(mouse_click) ){
            return;
        }
        SDL_Flip(ecran);
    }
}

int mouse_on_arrow(SDL_Rect pos){
    if(pos.x >12 && pos.x <53 && pos.y >12 && pos.y <48 ){ return 1; }
    return 0;
}
