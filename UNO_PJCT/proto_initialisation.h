#ifndef proto_fonctionss
#define proto_fonctionss
void charger_pile(int* pile);
void shuffle_cartes(int N);
void cacher_joeur_cartes(int joueur);
int charger_une_carte();
void initialiser_joueur_cartes(Joueur* player1, Joueur* player2, Joueur* player3,FMOD_SYSTEM *sys, FMOD_SOUND *sound1, FMOD_SOUND *sound2);
void commencer_jeu(FMOD_SYSTEM *sys, FMOD_SOUND *sound1, FMOD_SOUND *uno);
#endif // proto_fonctionss
