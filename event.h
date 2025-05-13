/*
Gère les différents évènements du jeu comme le mouvement des personnages et des ennemies, les collisions, le scroll de la map
et si le niveau est fini (win et loose). 
*/

#ifndef DEF_EVENT
#define DEF_EVENT
    
    #include "file.h"
    #include "charactere.h"

    int event(Personnage *mario, SDL_Renderer *renderer, SDL_Event event, int *img);
    void deplacer(Personnage *mario);
    void saut(Personnage *mario, int *img);
    void afficher_mario(Personnage *mario, int *img);


  
#endif