
#include "game.h"
#include "file.h"
#include "charactere.h"
#include "event.h"

int jouer(SDL_Renderer* renderer) {
    
	//charger image et personnage. 
	
    int continuer = 1;
    SDL_Event events;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    while(continuer){ //coeur du jeu ici, les actions seront repété pour faire le déplacement des différentes images, ...
        SDL_RenderClear(renderer);
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
                
				
            }
            switch (events.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            }
        }
        
		//on gère les divers events.
		
        SDL_RenderPresent(renderer); // affiche le tout
        
        
    }
    
	//a vous de compléter, au fur et à mesure, les deux fonctions en dessous pour bien faire le nettoyage. 
    //LibererMap(map, sprites);
    //freePersonnage(mario, goomba, nbGoomba);

    return continuer;
}