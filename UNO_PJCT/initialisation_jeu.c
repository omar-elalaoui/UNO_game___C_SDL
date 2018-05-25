#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <fmodex/fmod.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "const_globls.h"
#include "proto_initialisation.h"

/*----------------------------------------les variables Globales--------------------------------------------*/
SDL_Surface  *background,*pile_img,*cartes[54],*black,*colors,*s_carte,*fleche[8], *fin;
SDL_Rect     position_pile, positionTop_Cart;
int  top_carte, *pile, nombre_cartes;
extern SDL_Surface *ecran, *pointer, *hand;
/*--------------------------------------------fin variables Globales----------------------------------------*/
void lancer_jeu(SDL_Surface* ecran, FMOD_SYSTEM *sys, FMOD_SOUND *sound1, FMOD_SOUND *sound2, FMOD_SOUND *uno){

/*------------------------------------------les variables Locales------------------------------------------*/
        int i;
        nombre_cartes=108;
        pile=(int*)malloc(sizeof(int)*nombre_cartes);
        charger_pile(pile);

/*--------------------------------------------fin variable--------------------------------------------------*/

/*--------------------------------Inisialisation des cartes de chaque joueurs a vide------------------------*/
                        for(i=0; i<JOUEUR_CASES; i++){
                            joueur1.carte[i]=vide ;
                            joueur2.carte[i]=vide ;
                            joueur3.carte[i]=vide ;
                        }

/*------------------------------------------------------les positions---------------------------------------------------------------*/
            positionTop_Cart.x=545;   position_pile.x=1033;
            positionTop_Cart.y=72;    position_pile.y=40;

            joueur1.position.x= P_POS_X;     joueur2.position.x= P_POS_X;      joueur3.position.x= P_POS_X;
            joueur1.position.y= P1_POS_Y;    joueur2.position.y= P2_POS_Y;     joueur3.position.y= P3_POS_Y;

            joueur1.position_avatar.x=25;   joueur2.position_avatar.x=25;  joueur3.position_avatar.x=25;
            joueur1.position_avatar.y=602;  joueur2.position_avatar.y=479;  joueur3.position_avatar.y=356;
/*--------------------------------------------------fin les positions---------------------------------------------------------------*/



/*-----------------------------on charge les images----------------------------*/
        background=IMG_Load("img/background.bmp");      pile_img=IMG_Load("img/cards/sCart.png");
        black=IMG_Load("img/black.bmp");                colors=IMG_Load("img/colors.png");
        s_carte= IMG_Load("img/s_carte.png");
        SDL_SetAlpha(black, SDL_SRCALPHA, 185);

        joueur1.avatar=IMG_Load("img/avatars/avatar1.png");
        joueur2.avatar=IMG_Load("img/avatars/avatar2.png");
        joueur3.avatar=IMG_Load("img/avatars/avatar3.png");

        fleche[rouge_haut]=IMG_Load("img/fleches/rouge_haut.png");   fleche[rouge_bas]=IMG_Load("img/fleches/rouge_bas.png");
        fleche[bleu_haut]=IMG_Load("img/fleches/bleu_haut.png");     fleche[bleu_bas]=IMG_Load("img/fleches/bleu_bas.png");
        fleche[vert_haut]=IMG_Load("img/fleches/vert_haut.png");     fleche[vert_bas]=IMG_Load("img/fleches/vert_bas.png");
        fleche[jaune_haut]=IMG_Load("img/fleches/jaune_haut.png");   fleche[jaune_bas]=IMG_Load("img/fleches/jaune_bas.png");


        cartes[r0]=IMG_Load("img/cards/r0.png");        cartes[b0]=IMG_Load("img/cards/b0.png");
        cartes[r1]=IMG_Load("img/cards/r1.png");        cartes[b1]=IMG_Load("img/cards/b1.png");
        cartes[r2]=IMG_Load("img/cards/r2.png");        cartes[b2]=IMG_Load("img/cards/b2.png");
        cartes[r3]=IMG_Load("img/cards/r3.png");        cartes[b3]=IMG_Load("img/cards/b3.png");
        cartes[r4]=IMG_Load("img/cards/r4.png");        cartes[b4]=IMG_Load("img/cards/b4.png");
        cartes[r5]=IMG_Load("img/cards/r5.png");        cartes[b5]=IMG_Load("img/cards/b5.png");
        cartes[r6]=IMG_Load("img/cards/r6.png");        cartes[b6]=IMG_Load("img/cards/b6.png");
        cartes[r7]=IMG_Load("img/cards/r7.png");        cartes[b7]=IMG_Load("img/cards/b7.png");
        cartes[r8]=IMG_Load("img/cards/r8.png");        cartes[b8]=IMG_Load("img/cards/b8.png");
        cartes[r9]=IMG_Load("img/cards/r9.png");        cartes[b9]=IMG_Load("img/cards/b9.png");

        cartes[v0]=IMG_Load("img/cards/v0.png");        cartes[j0]=IMG_Load("img/cards/j0.png");
        cartes[v1]=IMG_Load("img/cards/v1.png");        cartes[j1]=IMG_Load("img/cards/j1.png");
        cartes[v2]=IMG_Load("img/cards/v2.png");        cartes[j2]=IMG_Load("img/cards/j2.png");
        cartes[v3]=IMG_Load("img/cards/v3.png");        cartes[j3]=IMG_Load("img/cards/j3.png");
        cartes[v4]=IMG_Load("img/cards/v4.png");        cartes[j4]=IMG_Load("img/cards/j4.png");
        cartes[v5]=IMG_Load("img/cards/v5.png");        cartes[j5]=IMG_Load("img/cards/j5.png");
        cartes[v6]=IMG_Load("img/cards/v6.png");        cartes[j6]=IMG_Load("img/cards/j6.png");
        cartes[v7]=IMG_Load("img/cards/v7.png");        cartes[j7]=IMG_Load("img/cards/j7.png");
        cartes[v8]=IMG_Load("img/cards/v8.png");        cartes[j8]=IMG_Load("img/cards/j8.png");
        cartes[v9]=IMG_Load("img/cards/v9.png");        cartes[j9]=IMG_Load("img/cards/j9.png");

        cartes[rInv]=IMG_Load("img/cards/rInv.png");      cartes[bInv]=IMG_Load("img/cards/bInv.png");
        cartes[rPlus2]=IMG_Load("img/cards/rPlus2.png");  cartes[bPlus2]=IMG_Load("img/cards/bPlus2.png");
        cartes[rSkip]=IMG_Load("img/cards/rSkip.png");    cartes[bSkip]=IMG_Load("img/cards/bSkip.png");

        cartes[vInv]=IMG_Load("img/cards/vInv.png");      cartes[jInv]=IMG_Load("img/cards/jInv.png");
        cartes[vPlus2]=IMG_Load("img/cards/vPlus2.png");  cartes[jPlus2]=IMG_Load("img/cards/jPlus2.png");
        cartes[vSkip]=IMG_Load("img/cards/vSkip.png");    cartes[jSkip]=IMG_Load("img/cards/jSkip.png");

        cartes[joker]=IMG_Load("img/cards/joker.png");
        cartes[plus4]=IMG_Load("img/cards/plus4.png");

        fin=IMG_Load("img/win.png");
/*-----------------------------fin de chargement----------------------------*/

        shuffle_cartes(nombre_cartes); //on mélange les cartes

/*---------------------------on charge la carte de top et les carte de chaque joueur-------------------------------*/
        initialiser_joueur_cartes(&joueur1, &joueur2, &joueur3, sys, sound1, sound2);


        commencer_jeu(sys, sound1, uno);
        /*----------------------Free surfaces -------------*/

    free(pile);
    for(i=0; i<54; i++) SDL_FreeSurface(cartes[i]);
    for(i=0; i<8; i++)  SDL_FreeSurface(fleche[i]);
    SDL_FreeSurface(s_carte);
    SDL_FreeSurface(black);
    SDL_FreeSurface(colors);
    SDL_FreeSurface(background);
/*--------------------end Free surfaces -------------*/
}




void charger_pile(int* pile){
     int tab[]={ r0,b0,v0,j0,   r1,r2,r3,r4,r5,r6,r7,r8,r9,r1,r2,r3,r4,r5,r6,r7,r8,r9,
                                b1,b2,b3,b4,b5,b6,b7,b8,b9,b1,b2,b3,b4,b5,b6,b7,b8,b9,
                                v1,v2,v3,v4,v5,v6,v7,v8,v9,v1,v2,v3,v4,v5,v6,v7,v8,v9,
                                j1,j2,j3,j4,j5,j6,j7,j8,j9,j1,j2,j3,j4,j5,j6,j7,j8,j9,
                                rInv,rPlus2,rSkip,bInv,bPlus2,bSkip,vInv,vPlus2,vSkip,jInv,jPlus2,jSkip,
                                rInv,rPlus2,rSkip,bInv,bPlus2,bSkip,vInv,vPlus2,vSkip,jInv,jPlus2,jSkip,
                                joker,joker,joker,joker, plus4,plus4,plus4,plus4
               };
    memcpy(pile, tab, sizeof(tab));
}

void shuffle_cartes(int N){
    int i, index, temp;
    srand(time(NULL));
    for(i=0; i<N; i++){ temp= pile[i]; index= rand()%N; pile[i]=pile[index]; pile[index]= temp; }
}

int charger_une_carte(){
    int i, temp=pile[0];
    for(i=0; i<(nombre_cartes-1); i++){ pile[i]=pile[i+1]; }
    nombre_cartes--;  pile=(int*)realloc(pile, sizeof(int)*nombre_cartes);
    return temp;
}

void initialiser_joueur_cartes(Joueur* player1, Joueur* player2, Joueur* player3, FMOD_SYSTEM *sys, FMOD_SOUND *sound1, FMOD_SOUND *sound2){
    int i;


        top_carte=charger_une_carte();
        SDL_BlitSurface(background, NULL, ecran, NULL);
        SDL_BlitSurface(player1->avatar, NULL, ecran, &player1->position_avatar);
        SDL_Flip(ecran);
        FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound2, 0, NULL);
        SDL_Delay(1000);
    for(i=0; i<7; i++){
        player1->carte[i+4]= charger_une_carte();
        SDL_Delay(250);
        cacher_joeur_cartes(J1);
        SDL_Flip(ecran);
        FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound1, 0, NULL);
    }
    SDL_BlitSurface(player2->avatar, NULL, ecran, &player2->position_avatar);
    SDL_Delay(500);
    for(i=0; i<7; i++){
        player2->carte[i+4]= charger_une_carte();
        SDL_Delay(250);
        cacher_joeur_cartes(J2);
        SDL_Flip(ecran);
        FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound1, 0, NULL);
    }
    SDL_BlitSurface(player3->avatar, NULL, ecran, &player3->position_avatar);
    SDL_Delay(500);
    for(i=0; i<7; i++){
        player3->carte[i+4]= charger_une_carte();
        SDL_Delay(250);
        cacher_joeur_cartes(J3);
        SDL_Flip(ecran);
        FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound1, 0, NULL);
    }
    SDL_Delay(1000);
    SDL_BlitSurface(s_carte, NULL, ecran, &positionTop_Cart);
    SDL_Flip(ecran);
    FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound1, 0, NULL);
    SDL_Delay(1000);
    FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound2, 0, NULL);
    SDL_Delay(1500);
    SDL_BlitSurface(pile_img, NULL, ecran, &position_pile);
    SDL_Flip(ecran);
    SDL_Delay(500);
    SDL_BlitSurface(cartes[top_carte], NULL, ecran, &positionTop_Cart);
    SDL_Flip(ecran);
    FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound1, 0, NULL);
    SDL_Delay(1000);
    FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound1, 0, NULL);
}














