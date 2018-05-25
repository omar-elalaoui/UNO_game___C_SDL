#ifndef HEADER
#define HEADER
#define W_C 60
#define H_C 85
#define JOUEUR_CASES 17
#define P_POS_X  W_C*2
#define P1_POS_Y 588
#define P2_POS_Y 465
#define P3_POS_Y 342
#define F_POS_X 96
#define F3_POS_Y 385
#define F2_POS_Y 504
#define F1_POS_Y 631
enum cartes{  r0,r1,r2,r3,r4,r5,r6,r7,r8,r9, b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,
              v0,v1,v2,v3,v4,v5,v6,v7,v8,v9, j0,j1,j2,j3,j4,j5,j6,j7,j8,j9,
              rInv,rPlus2,rSkip,  bInv,bPlus2,bSkip,  vInv,vPlus2,vSkip,  jInv,jPlus2,jSkip, joker, plus4,  vide};
enum fleches{ rouge_haut, rouge_bas, bleu_haut, bleu_bas, vert_haut, vert_bas, jaune_haut, jaune_bas };
enum Joueurs{ J1=1, J2, J3 };
enum Couleurs{ rouge= -9, vert, bleu, jaune};
enum{ plus2= -5, skip, inv, pile_click};

typedef struct Joueur{
    int carte[JOUEUR_CASES];
    SDL_Surface *avatar;
    SDL_Rect position_avatar;
    SDL_Rect position;
}Joueur;
Joueur joueur1, joueur2, joueur3;
#endif // header


