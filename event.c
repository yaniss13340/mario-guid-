#include "event.h"
#include "charactere.h"

void deplacer(Personnage *mario);
int statique(Personnage *mario);
void saut(Personnage *mario, int *img);
void afficher_mario(Personnage *mario, int *img);

int event(Personnage *mario, SDL_Renderer *renderer, SDL_Event event, int *img){
    switch (event.type){
        case SDL_QUIT:
            return 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym){
                case SDLK_RIGHT:
                    mario->direction = 1;
                    mario->dernieredirection = mario->direction;
                    break;
                case SDLK_LEFT:
                    mario->direction = 2;
                    mario->dernieredirection = mario->direction;
                    break;
                case SDLK_UP:
                    mario->jump = 1;
                    break;
                case SDLK_ESCAPE:
                    return 0;
                    break;
                default:
                    break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym){
                case SDLK_RIGHT:
                case SDLK_LEFT:
                    mario->direction = 0;
                    *img = statique(mario);
                    break;
                default:
                    break;                    
            }
        default:
            break;
    }
    return 1;
}

void deplacer(Personnage *mario){
    if(mario->direction == 1){
        mario->position.x += 2;
    } else if(mario->direction == 2){
        mario->position.x -= 2;
    }
}

int statique(Personnage *mario){
    if(mario->dernieredirection == 1){
        return MARIO_DROITE;
    } else if(mario->dernieredirection == 2){
        return MARIO_GAUCHE;
    }
}

void saut(Personnage *mario, int *img){
    if(mario->jump == 1){
        mario->position.y -= 2;
        mario->jumptime += 2;
    }
    if(mario->jumptime >= 70){
        mario->jump = 0;
    }
    if(mario->jumptime > 0 && mario->jump == 0){
        mario->position.y += 2;
        mario->jumptime -= 2;
    }
    if(mario->jump == 0 && mario->jumptime == 0){
        *img = statique(mario);
    }
}

void afficher_mario(Personnage *mario, int *img){
    if(mario->direction == 1){
        if(mario->jumptime > 0){
            *img = MARIO_DROITE_SAUT;
        } else {
            *img = MARIO_DROITE_COURS;
        }
    } else if(mario->direction == 2){
        if(mario->jumptime > 0){
            *img = MARIO_GAUCHE_SAUT;
        } else {
            *img = MARIO_GAUCHE_COURS;
        }
    }else if(mario->jumptime > 0){
        if(mario->dernieredirection == 1){
            *img = MARIO_DROITE_SAUT;
        } else if(mario->dernieredirection == 2){
            *img = MARIO_GAUCHE_SAUT;
        }
    }
}