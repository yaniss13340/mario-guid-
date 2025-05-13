#include <SDL2/SDL_image.h>

#include "file.h"

/*permetde charger une image dans une SDL_Texture avec l'option SDL_TEXTUREACCESS_TARGET
pour pouvoir modifier la texture après. */
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *surface = NULL; 
    SDL_Texture *tmp = NULL, *texture = NULL;
    surface = IMG_Load(path);
    if(NULL == surface)
    {
        fprintf(stderr, "Erreur IMG_Load : %s", SDL_GetError());
        return NULL;
    }
    tmp = SDL_CreateTextureFromSurface(renderer, surface);
    if(NULL == tmp)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
                            SDL_TEXTUREACCESS_TARGET, surface->w, surface->h); 
    if(texture == NULL) 
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    SDL_SetRenderTarget(renderer, texture); /* La cible de rendu est maintenant texture. */
    SDL_SetTextureBlendMode(tmp, SDL_BLENDMODE_NONE); /* gère la transparence du fond des images*/
    SDL_RenderCopy(renderer, tmp, NULL, NULL); /* On copie tmp sur texture */
    SDL_DestroyTexture(tmp); //nettoyage
    SDL_FreeSurface(surface); //nettoyage
    SDL_SetRenderTarget(renderer, NULL); /* La cible de rendu est de nouveau le renderer. */
    return texture;
}


void LireLevel0(Map* map) {
    FILE *fichier = fopen("level/niveau0.lvl", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier niveau0.lvl");
        return;
    }

    char ligne[100];
    if (fgets(ligne, sizeof(ligne), fichier) == NULL) {
        fprintf(stderr, "Erreur lors de la lecture du nom du niveau\n");
        fclose(fichier);
        return;
    }

    int largeur, hauteur;
    if (fscanf(fichier, "%d %d", &largeur, &hauteur) != 2) {
        fprintf(stderr, "Erreur lors de la lecture des dimensions de la map\n");
        fclose(fichier);
        return;
    }

    if (largeur <= 0 || hauteur <= 0) {
        fprintf(stderr, "Dimensions invalides : largeur = %d, hauteur = %d\n", largeur, hauteur);
        fclose(fichier);
        return;
    }

    printf("Largeur : %d, Hauteur : %d\n", largeur, hauteur);

    map->width = largeur;
    map->height = hauteur;

    // Allocation du tableau 2D
    map->LoadedMap = malloc(map->height * sizeof(int*));
    if (map->LoadedMap == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour LoadedMap\n");
        fclose(fichier);
        return;
    }

    for (int i = 0; i < map->height; i++) {
        map->LoadedMap[i] = malloc(map->width * sizeof(int));
        if (map->LoadedMap[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour LoadedMap[%d]\n", i);
            for (int j = 0; j < i; j++) {
                free(map->LoadedMap[j]);
            }
            free(map->LoadedMap);
            fclose(fichier);
            return;
        }
    }

    // Lecture des données de la map
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            if (fscanf(fichier, "%d", &map->LoadedMap[i][j]) != 1) {
                fprintf(stderr, "Erreur lors de la lecture des données de la map\n");
                for (int k = 0; k < map->height; k++) {
                    free(map->LoadedMap[k]);
                }
                free(map->LoadedMap);
                fclose(fichier);
                return;
            }
        }
    }

    fclose(fichier);
    printf("Map chargée avec succès.\n");
}

void AfficherMap(Map* map) {
    if (map->LoadedMap == NULL || map->width <= 0 || map->height <= 0) {
        fprintf(stderr, "Erreur : la map n'est pas valide ou n'a pas été chargée\n");
        return;
    }

    printf("Affichage de la map :\n");
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            printf("%d ", map->LoadedMap[i][j]);
        }
        printf("\n");
    }
}