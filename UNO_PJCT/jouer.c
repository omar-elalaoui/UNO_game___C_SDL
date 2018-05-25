#include<SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <fmodex/fmod.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "const_globls.h"
#include "proto_initialisation.h"
#include "proto_jouer.h"
extern SDL_Surface *ecran, *background, *pile_img, *cartes[54], *pointer, *hand, *black, *colors, *s_carte, *fleche[8],*fin;
extern SDL_Rect    position_pile, positionTop_Cart;
extern int  top_carte, *pile, nombre_cartes;
void commencer_jeu(FMOD_SYSTEM *sys, FMOD_SOUND *sound1, FMOD_SOUND *uno){


    int quitter=0 , r, joueur=1, carte_a_jouer=top_carte, direction=1;
    r=jouer(joueur, direction, &carte_a_jouer, &quitter, sys, sound1, uno);
    while(!quitter){
        switch(r){
            case rPlus2:
            case bPlus2:
            case vPlus2:
            case jPlus2:
                joueur= direction? (joueur%3)+1 : ((joueur+1)%3)+1;
                shuffle_cartes(nombre_cartes);
                distribuer(joueur, 2, sys, sound1);
                joueur= direction? (joueur%3)+1 : ((joueur+1)%3)+1;
                r=jouer(joueur, direction, &carte_a_jouer, &quitter, sys, sound1, uno);
            break;

            case plus4:
                joueur= direction? (joueur%3)+1 : ((joueur+1)%3)+1;
                shuffle_cartes(nombre_cartes);
                distribuer(joueur, 4, sys, sound1);
                carte_a_jouer= direction? choisir_une_couleur( ((joueur+1)%3)+1 ) : choisir_une_couleur( (joueur%3)+1 );
                joueur= direction? (joueur%3)+1 : ((joueur+1)%3)+1;
                r=jouer(joueur, direction, &carte_a_jouer, &quitter, sys, sound1, uno);
            break;

            case joker:
                carte_a_jouer= choisir_une_couleur(joueur);
                joueur= direction? (joueur%3)+1 : ((joueur+1)%3)+1;
                r=jouer(joueur, direction, &carte_a_jouer, &quitter, sys, sound1, uno);
            break;

            case rInv:
            case bInv:
            case vInv:
            case jInv:
                direction= !direction;
                joueur= direction? (joueur%3)+1 : ((joueur+1)%3)+1;
                r=jouer(joueur, direction, &carte_a_jouer, &quitter, sys, sound1, uno);
            break;

            case rSkip:
            case bSkip:
            case vSkip:
            case jSkip:
                joueur= direction? (joueur%3)+1 : ((joueur+1)%3)+1;
                joueur= direction? (joueur%3)+1 : ((joueur+1)%3)+1;
                r=jouer(joueur, direction, &carte_a_jouer, &quitter, sys, sound1, uno);
            break;

            case pile_click:
                shuffle_cartes(nombre_cartes);
                distribuer(joueur, 1, sys, sound1);
                joueur= direction? (joueur%3)+1 : ((joueur+1)%3)+1;
                r=jouer(joueur, direction, &carte_a_jouer, &quitter, sys, sound1, uno);
            break;

            default:
                joueur= direction? (joueur%3)+1 : ((joueur+1)%3)+1;
                r=jouer(joueur, direction, &carte_a_jouer, &quitter, sys, sound1, uno);
        }
    }
}

int jouer(int joueur, int direction, int* carte, int* quitter, FMOD_SYSTEM *sys, FMOD_SOUND *sound, FMOD_SOUND *uno){

    SDL_Event e;
    SDL_Rect position_mouse, position_button;
    Joueur* player;
    int cc=1, j, havered_carte=vide, clicked_carte, index_button;
    player=recuperer_joueur(joueur);
    while(cc){
        SDL_PollEvent(&e);
        switch(e.type){
            case SDL_QUIT:
                cc=0; *quitter=1;
            break;
            case SDL_MOUSEMOTION:
                position_mouse.x= e.motion.x;
                position_mouse.y= e.motion.y;
            break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT){
                    position_button.x= e.button.x;
                    position_button.y= e.button.y;
                }
        }

        SDL_BlitSurface(background, NULL, ecran, NULL);
        SDL_BlitSurface(pile_img, NULL, ecran, &position_pile);
        SDL_BlitSurface(cartes[top_carte], NULL, ecran, &positionTop_Cart);
        SDL_BlitSurface(joueur1.avatar, NULL, ecran, &joueur1.position_avatar);
        SDL_BlitSurface(joueur2.avatar, NULL, ecran, &joueur2.position_avatar);
        SDL_BlitSurface(joueur3.avatar, NULL, ecran, &joueur3.position_avatar);
        afficher_joueur_flech(joueur, *carte, direction);

        if( check_position_button(joueur, position_button, &clicked_carte, &index_button) ){
                if(clicked_carte == pile_click){ return pile_click; }
                if(areMatched(clicked_carte, *carte)){
                    ajouter_aux_cartes(top_carte);
                    top_carte=clicked_carte;
                   if( (doit_decaler(player, NULL) == 1) ){ decaler_vers_droite(player, index_button); }
                   else{ decaler_vers_gauche(player, index_button); }
                   if( (clicked_carte != joker) && (clicked_carte != plus4) ){ *carte=clicked_carte; }
                   if( (clicked_carte != rPlus2) && (clicked_carte != vPlus2) && (clicked_carte != jPlus2) && (clicked_carte != bPlus2) && (clicked_carte != plus4) ){
                    FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound, 0, NULL); }
                   SDL_Delay(250);
                   return clicked_carte;
                }
         }

        if(uno_click(position_button)){
            SDL_Delay(50);
            FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, uno, 0, NULL);
            SDL_Delay(50);
            position_button.x=0;
        }

        if( (check_position_mouse(joueur, position_mouse, &havered_carte)) ){
            afficher_joeur_cartes(joueur, havered_carte);
            j=(joueur%3)+1;
            cacher_joeur_cartes(j);
            j=(j%3)+1;
            cacher_joeur_cartes(j);

            position_mouse.x -=5;
            SDL_BlitSurface(hand, NULL, ecran, &position_mouse);
            position_mouse.x +=5;
        }

        else{
        afficher_joeur_cartes(joueur, -1);
        j=(joueur%3)+1;
        cacher_joeur_cartes(j);
        j=(j%3)+1;
        cacher_joeur_cartes(j);
        SDL_BlitSurface(pointer, NULL, ecran, &position_mouse);
        }
        SDL_Flip(ecran);
    }
    return -15;
}
/*----------fin de fonction jouer-----------*/

Joueur* recuperer_joueur(int joueur){
    switch(joueur){
    case J1:
        return &joueur1;

    case J2:
        return &joueur2;

    case J3:
        return &joueur3;
    }
return NULL;
}

int check_position_mouse(int joueur, SDL_Rect pos, int* havered_carte){
    int i;
    Joueur* player;
    player=recuperer_joueur(joueur);
            if( (pos.y > player->position.y && pos.y < (player->position.y + H_C)) ){
            for(i=0; i< JOUEUR_CASES; i++){
                if(player->carte[i] != vide){ if(pos.x > (P_POS_X +W_C*i) && pos.x < (3*W_C+W_C*i - 5)){ *havered_carte=i; return 1; } }
            }}

    if( (pos.x > position_pile.x && pos.x < (position_pile.x + 67)) && ( pos.y > 40 && pos.y < (40 + 97) ) ){ *havered_carte=vide; return 1; }
    if( pos.x >35 && pos.x <115 && pos.y >35 && pos.y <115 ) { *havered_carte=vide; return 1; }
    return 0;
}

void afficher_joeur_cartes(int joueur, int index){
    int i;
    Joueur* player;
    player=recuperer_joueur(joueur);
        for(i=0; i<JOUEUR_CASES; i++){
            if(player->carte[i] !=  vide){
                if(i == index){
                    player->position.y -= 10;
                    SDL_BlitSurface(cartes[player->carte[i]], NULL, ecran, &player->position);
                    player->position.y += 10;
                }
                else{ SDL_BlitSurface(cartes[player->carte[i]], NULL, ecran, &player->position); }
             }
            player->position.x += W_C;
    }
    player->position.x = P_POS_X;
}

void cacher_joeur_cartes(int joueur){
    int i;
    Joueur* player;
    player=recuperer_joueur(joueur);
        for(i=0; i<JOUEUR_CASES; i++){
            if(player->carte[i] !=  vide){
                SDL_BlitSurface(s_carte, NULL, ecran, &player->position);
             }
            player->position.x += W_C;
        }
    player->position.x = P_POS_X;
}

int check_position_button(int joueur, SDL_Rect pos,int* carte, int* index){
    int i;
    Joueur* player=recuperer_joueur(joueur);
            if( pos.y > player->position.y && pos.y < (player->position.y + H_C) ){
            for(i=0; i< JOUEUR_CASES; i++){
                if(player->carte[i] != vide){ if(pos.x >(P_POS_X +W_C*i) && pos.x < (3*W_C+W_C*i - 5)){
                    *index=i;
                    *carte=player->carte[i];
                return 1; }}
            }}

    if( (pos.x > position_pile.x && pos.x < (position_pile.x + 67)) && ( pos.y > 40 && pos.y < (40 + 97) ) ){
            *carte=pile_click;
            return 1;
    }

return 0;}

void ajouter_aux_cartes(int carte){
    nombre_cartes++; pile=(int*)realloc(pile, 4*nombre_cartes);
    pile[nombre_cartes-1]=carte;
}

int areMatched(int clicked_carte, int carte){
    int color1, color2, number_carac1, number_carac2;

    color2=what_color(clicked_carte);
    number_carac2=what_number_carac(clicked_carte);
    if( (clicked_carte == joker) || (clicked_carte == plus4) || (carte == color2) ) return 1;
    else{
        color1=what_color(carte);
        number_carac1=what_number_carac(carte);
        if( (color1 == color2) || (number_carac1 == number_carac2) ) return 1;
    }

return 0;}

int what_color(int carte){
    if( (carte >= r0 && carte <= r9) || carte == rInv || carte == rSkip || carte == rPlus2) return rouge;
    if( (carte >= b0 && carte <= b9) || carte == bInv || carte == bSkip || carte == bPlus2) return bleu;
    if( (carte >= v0 && carte <= v9) || carte == vInv || carte == vSkip || carte == vPlus2) return vert;
    if( (carte >= j0 && carte <= j9) || carte == jInv || carte == jSkip || carte == jPlus2) return jaune;
    switch(carte){
        case rouge:
            return rouge;

        case vert:
            return vert;

        case bleu:
            return bleu;

        case jaune:
            return jaune;
    }
    return -10;
}

int what_number_carac(int carte){
    if(carte == r0 || carte == b0 || carte == v0 || carte == j0 ) return 0;
    if(carte == r1 || carte == b1 || carte == v1 || carte == j1 ) return 1;
    if(carte == r2 || carte == b2 || carte == v2 || carte == j2 ) return 2;
    if(carte == r3 || carte == b3 || carte == v3 || carte == j3 ) return 3;
    if(carte == r4 || carte == b4 || carte == v4 || carte == j4 ) return 4;
    if(carte == r5 || carte == b5 || carte == v5 || carte == j5 ) return 5;
    if(carte == r6 || carte == b6 || carte == v6 || carte == j6 ) return 6;
    if(carte == r7 || carte == b7 || carte == v7 || carte == j7 ) return 7;
    if(carte == r8 || carte == b8 || carte == v8 || carte == j8 ) return 8;
    if(carte == r9 || carte == b9 || carte == v9 || carte == j9 ) return 9;
    if(carte == rPlus2 || carte == bPlus2 || carte == vPlus2 || carte == jPlus2 ) return plus2;
    if(carte == rSkip || carte == bSkip || carte == vSkip || carte == jSkip ) return skip;
    if(carte == rInv || carte == bInv || carte == vInv || carte == jInv ) return inv;
    return -9;
}

void decaler_vers_droite(Joueur* player, int index){
    if(index == 0){
        player->carte[index]=vide;
        return;}
    while(player->carte[index-1] != vide && index != 0){
        player->carte[index]= player->carte[index-1];
        index--;
    }
    player->carte[index]=vide;
}

void distribuer(int joueur, int N, FMOD_SYSTEM *sys, FMOD_SOUND *sound){
    int i, decalage_index;
    Joueur* player;
    player= recuperer_joueur(joueur);
    for(i=0; i<N; i++){
        if( (doit_decaler(player, &decalage_index) == -1) ){ decaler_vers_gauche(player, decalage_index); }
        distribuer_une_carte(player);
        cacher_joeur_cartes(J1);
        cacher_joeur_cartes(J2);
        cacher_joeur_cartes(J3);
        SDL_Flip(ecran);
        FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound, 0, NULL);
        SDL_Delay(400);
    }
    SDL_Delay(100);
}

int doit_decaler(Joueur* player, int* index){
    int i=0, r=0, j=JOUEUR_CASES-3;
        while(player->carte[i] == vide) i++;
        while(player->carte[j] == vide){ j--; r++; }
        if( index != NULL ) *index=i-1;
        if( r == i) return 0;
        return r > i ? 1 : -1;
}

void decaler_vers_gauche(Joueur* player, int index){
    if(index == JOUEUR_CASES-1){
        player->carte[index]=vide;
        return;
    }
    while(player->carte[index+1] != vide && index != JOUEUR_CASES-1){
        player->carte[index]= player->carte[index+1];
        index++;
    }
    player->carte[index]=vide;
}

void distribuer_une_carte(Joueur* player){
    int i= JOUEUR_CASES-1;
    while(player->carte[i] == vide) i--;
    player->carte[i+1]=charger_une_carte();
}

int choisir_une_couleur(int joueur){
    int cc=1, color=-1, j;
    SDL_Rect position_colors, mouse_position, button_position;
    SDL_Event e;
    position_colors.x=355;
    position_colors.y=15;
        while(cc){
            SDL_WaitEvent(&e);
            switch(e.type){
                case SDL_QUIT:
                    cc=0;
                break;
                case SDL_MOUSEMOTION:
                    mouse_position.x=e.motion.x;
                    mouse_position.y=e.motion.y;
                break;
                case SDL_MOUSEBUTTONDOWN:
                    button_position.x=e.button.x;
                    button_position.y=e.button.y;
            }

        SDL_BlitSurface(background, NULL, ecran, NULL);
        SDL_BlitSurface(pile_img, NULL, ecran, &position_pile);
        SDL_BlitSurface(cartes[top_carte], NULL, ecran, &positionTop_Cart);
        afficher_joeur_cartes(joueur, -1);
        j=(joueur%3)+1;
        cacher_joeur_cartes(j);
        afficher_avatar(j);
        j=(j%3)+1;
        cacher_joeur_cartes(j);
        afficher_avatar(j);

        if(check_mouse_on_colors(mouse_position)){
            SDL_BlitSurface(black, NULL, ecran, NULL);
            SDL_BlitSurface(colors, NULL, ecran, &position_colors);
            afficher_joeur_cartes(joueur, -1);
            afficher_avatar(joueur);
            SDL_BlitSurface(hand, NULL, ecran, &mouse_position);
        }
        else{
            SDL_BlitSurface(black, NULL, ecran, NULL);
            SDL_BlitSurface(colors, NULL, ecran, &position_colors);
            afficher_joeur_cartes(joueur, -1);
            afficher_avatar(joueur);
            SDL_BlitSurface(pointer, NULL, ecran, &mouse_position);
        }
        if(check_selected_color(button_position, &color)) return color;
       SDL_Flip(ecran);
    }
    return -17;
}

int check_mouse_on_colors(SDL_Rect pos){
    int i;
    if( pos.y > 15 && pos.y <  157 ){
        for(i=0; i<4; i++){
            if( pos.x > (420+ 77*i) && pos.x < (420+ 77*i +53) ) return 1;
        }
    }
    return 0;
}

int check_selected_color(SDL_Rect pos, int* color){
    int i;
    if( pos.y > 15 && pos.y < 157 ){
        for(i=0; i<4; i++){ if( pos.x > (420+ 77*i) && pos.x < (420+ 77*i +53) ){ *color=rouge+ i; return 1; } }
    }
    return 0;
}

void afficher_joueur_flech(int joueur, int carte, int direction){
    int i;
    SDL_Rect position;
    position.x=F_POS_X;
        switch(joueur){
            case J1:
                position.y=F1_POS_Y;
            break;
            case J2:
                position.y=F2_POS_Y;
            break;
            case J3:
                position.y=F3_POS_Y;
        }
    i=index_fleche(carte, direction);
    SDL_BlitSurface(fleche[i], NULL, ecran, &position);
}

int index_fleche(int carte, int direction){
    int coleur;
    coleur=what_color(carte);
    switch(coleur){
        case rouge:
            return direction? rouge_haut : rouge_bas;
        case bleu:
            return direction? bleu_haut : bleu_bas;
        case vert:
            return direction? vert_haut : vert_bas;
        case jaune:
            return direction? jaune_haut : jaune_bas;
    }
    return -1;
}

void afficher_avatar(int joueur){
    Joueur* player;
    player=recuperer_joueur(joueur);
    SDL_BlitSurface(player->avatar, NULL, ecran, &player->position_avatar);
}

int uno_click(SDL_Rect pos){
    if( pos.x >35 && pos.x <115 && pos.y >35 && pos.y <115 ) return 1;
    return 0;
}
/*int fin_jeu(){
    int i, k=0;
    for(i=0; i<JOUEUR_CASES; i++){ if(joueur1.carte[i] != vide); k=1; }
    for(i=0; i<JOUEUR_CASES; i++){ if(joueur1.carte[i] != vide); k=2; }
    for(i=0; i<JOUEUR_CASES; i++){ if(joueur1.carte[i] != vide); k=3; }
    if( k != 1 && k != 2 && k != 3 ){ return 1; }
    return 0;
}

void afficher_fin(){
    int cc=1;
    SDL_Event e;
    SDL_BlitSurface(black, NULL, ecran, NULL);
    SDL_BlitSurface(fin, NULL, ecran, NULL);
    SDL_Flip(ecran);
    while(cc){
        SDL_WaitEvent(&e);
        switch(e.type){
            case SDL_QUIT:
                cc=0;
            break;
        }
    }
}
*/






