#ifndef PROTO_JOUER
#define PROTO_JOUER
int jouer(int joueur, int direction, int* carte, int* quitter, FMOD_SYSTEM *sys, FMOD_SOUND *sound, FMOD_SOUND *uno);
Joueur* recuperer_joueur(int joueur);
int check_position_mouse(int joueur, SDL_Rect pos, int* havered_carte);
int check_position_button(int joueur, SDL_Rect pos, int* carte, int* index);
void afficher_joeur_cartes(int joueur, int index);
void cacher_joeur_cartes(int joueur);
void ajouter_aux_cartes(int carte);
int areMatched(int clicked_carte, int carte);
int what_color(int carte);
int what_number_carac(int carte);
void decaler_vers_gauche(Joueur* player, int index);
void decaler_vers_droite(Joueur* player, int index);
void distribuer(int joueur, int N, FMOD_SYSTEM *sys, FMOD_SOUND *sound);
int doit_decaler(Joueur* player, int* index);
void distribuer_une_carte(Joueur* player);
int choisir_une_couleur(int joueur);
int check_mouse_on_colors(SDL_Rect pos);
int check_selected_color(SDL_Rect pos, int* color);
int selected_color(int color);
void afficher_joueur_flech(int joueur,int carte, int direction);
int index_fleche(int carte, int direction);
void afficher_avatar(int joueur);
int uno_click(SDL_Rect pos);
//int fin_jeu();
//void afficher_fin();
#endif // PROTO_JOUER
