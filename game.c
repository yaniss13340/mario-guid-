#include "game.h"
#include "file.h"
#include "charactere.h"
#include "event.h"

int jouer(SDL_Renderer* renderer) {

    // Initialisation de la map
    Map map = {0};
    LireLevel0(&map);

    // Initialisation des sprites
    Sprites sprites[NbSprites];
    InitialiserSprites(sprites, renderer);
    // Configuration de la couleur de fond (blanc)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
	//charger image et personnage. 
    SDL_Rect position_initiale = {30, 810, WIDTH_MARIO, HEIGHT_MARIO};
    Personnage mario;
    init_mario(&mario, renderer, position_initiale);
    int img_mario = MARIO_DROITE;

    int continuer = 1; //a utiliser pour savoir si on continue la boucle du jeu ou si on arrête. 
    SDL_Event events;
    int spriteNum;
    while(continuer){ //coeur du jeu ici, les actions seront repété pour faire le déplacement des différentes images, ...
        SDL_RenderClear(renderer);
        AfficherMapAvecSprites(&map, sprites, renderer); // Afficher la map avec les sprites
        SDL_PollEvent(&events);
        continuer = event(&mario, renderer, events, &img_mario);
        afficher_mario(&mario, &img_mario);
        deplacer(&mario);
        saut(&mario, &img_mario);
        spriteNum = map.LoadedMap[mario.position.y/Size_Sprite][mario.position.x/Size_Sprite];
        if(sprites[spriteNum].traverser == 1){
            SDL_Log("%d: Le bloc est traversable", spriteNum);
        } else{
            SDL_Log("%d: Le bloc n'est pas traversable", spriteNum);
        }
        SDL_RenderCopy(renderer, mario.image[img_mario], NULL, &mario.position);
        SDL_RenderPresent(renderer);
    }
    
	//a vous de compléter, au fur et à mesure, les deux fonctions en dessous pour bien faire le nettoyage. 
    //LibererMap(map, sprites);
    //freePersonnage(mario, goomba, nbGoomba)

    // Libération des ressources une fois le jeu terminé
    for (int i = 0; i < map.height; i++) {
        free(map.LoadedMap[i]); // Libération de chaque ligne du tableau
    }
    free(map.LoadedMap); // Libération du tableau principal

    for (int i = 0; i < NbSprites; i++) {
        SDL_DestroyTexture(sprites[i].sprite); // Libération des textures des sprites
    }

    return continuer;
}

void AfficherMapAvecSprites(Map* map, Sprites* sprites, SDL_Renderer* renderer) {
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            int spriteIndex = map->LoadedMap[i][j];
            if (spriteIndex >= 0 && spriteIndex < NbSprites) {
                SDL_Rect dest = { j * Size_Sprite, i * Size_Sprite, Size_Sprite, Size_Sprite };
                SDL_RenderCopy(renderer, sprites[spriteIndex].sprite, NULL, &dest);
            }
        }
    }
}

void InitialiserSprites(Sprites* sprites, SDL_Renderer* renderer) {
    sprites[0].sprite = loadImage("img/sky.png", renderer);
    sprites[0].traverser = 1; // Le ciel est traversable

    sprites[1].sprite = loadImage("img/sol.png", renderer);
    sprites[1].traverser = 0; // Le sol n'est pas traversable

    sprites[2].sprite = loadImage("img/block.png", renderer);
    sprites[2].traverser = 0; // Le bloc de pierre n'est pas traversable

    sprites[3].sprite = loadImage("img/boite.png", renderer);
    sprites[3].traverser = 0; // La boîte n'est pas traversable

    sprites[4].sprite = loadImage("img/tuyau1.png", renderer);
    sprites[4].traverser = 0; // Tuyau partie 1

    sprites[5].sprite = loadImage("img/tuyau2.png", renderer);
    sprites[5].traverser = 0; // Tuyau partie 2

    sprites[6].sprite = loadImage("img/tuyau3.png", renderer);
    sprites[6].traverser = 0; // Tuyau partie 3

    sprites[7].sprite = loadImage("img/tuyau4.png", renderer);
    sprites[7].traverser = 0; // Tuyau partie 4
}