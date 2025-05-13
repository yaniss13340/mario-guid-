#include <stdlib.h>
#include <stdio.h>
#include "charactere.h"

void freePersonnage(Personnage* mario, Personnage **goomba, int nbGoomba) {
    
}

void init_mario(Personnage *mario, SDL_Renderer *renderer, SDL_Rect pos){
    mario->image = malloc(sizeof(SDL_Texture*)*NUMBER_IMAGE_MARIO);
    mario->image[MARIO_DROITE] = loadImage("./img/Mario1.png", renderer);
    mario->image[MARIO_DROITE_COURS] = loadImage("./img/Mario2.png", renderer);
    mario->image[MARIO_DROITE_SAUT] = loadImage("./img/Mario3.png", renderer);
    mario->image[MARIO_GAUCHE] = loadImage("./img/Mario4.png", renderer);
    mario->image[MARIO_GAUCHE_COURS] = loadImage("./img/Mario5.png", renderer);
    mario->image[MARIO_GAUCHE_SAUT] = loadImage("./img/Mario6.png", renderer);
    mario->position = pos;
    mario->jump = 0;
    mario->jumptime = 0;
    mario->gravite = 0;
    mario->direction = 0;
    mario->dernieredirection = 0;
    mario->temp = 0;
    mario->win = 0; 
    mario->invisible = 0;
}