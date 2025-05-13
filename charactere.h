/*
Contient la création du charactère (mario) et les divers caractéristique qui le compose, pareil pour les monstres.
Va aussi gérer l'affichage des personnages et mosntres. 
Attention la map doit déjà être chargé avant de créer un charactère. 
*/

#ifndef DEF_CHARACTERE
#define DEF_CHARACTERE
    
    #include <SDL2/SDL.h>
    #include "file.h"
    #define MARIO_DROITE 0
    #define MARIO_DROITE_COURS 1
    #define MARIO_DROITE_SAUT 2
    #define MARIO_GAUCHE 3
    #define MARIO_GAUCHE_COURS 4
    #define MARIO_GAUCHE_SAUT 5


    #define WIDTH_MARIO 22.5 //largeur des images mario
    #define HEIGHT_MARIO 30 //hauteur des images mario
    #define NUMBER_IMAGE_MARIO 6 //nombre d'image de mario en tout

    typedef struct Personnage Personnage;
    struct Personnage
    {
        SDL_Texture** image; //contient toutes les images nécessaire pour mario (différentes direction et saut)
        SDL_Rect position; //sa position à l'instant t
        int jump; //Si mario saute lors de la montée du saut jump = 1, sinon 0
        int jumptime; //correspond à la durée depuis quand mario fait un saut, à 70 on arrête
        int gravite; //vaut 1 si mario est dans les air, 0 sinon. 
        int direction, dernieredirection; //direction vers laquelle est dirigé mario, 1 : droite, 2 : gauche, 0 : statique) 
        int temp; //permet de faire varier les sprites de mario dans le temps.
        int win; //vaut 1 si le personnage gagne, -1 si il perd, 0 sinon. 
        int invisible; //utilisé pour les goombas quand il meurt vaut 1 dans ce cas, 0 si en vit.
        int lvl, lvlperdu;
    };

    
    void freePersonnage(Personnage* mario, Personnage **goomba, int nbGoomba);
    void init_mario(Personnage *mario, SDL_Renderer *renderer, SDL_Rect pos);
    
#endif