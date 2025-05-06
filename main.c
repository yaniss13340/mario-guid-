#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "game.h"

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);

int main(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {

        printf("Erreur SDL_Init: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Fenêtre Vide",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          LARGEUR_FENETRE, HAUTEUR_FENETRE,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL)
    {

        printf("Erreur SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {

        printf("Erreur SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
    SDL_RenderClear(renderer);
    char path[] = "img/menu.jpg";
    SDL_Rect dstrect = {0, 0, 255, 255};
    SDL_RenderCopy(renderer, loadImage(path, renderer), NULL, NULL);

    SDL_RenderPresent(renderer);
    SDL_Event event;
    int continuer = 1;
    while (SDL_PollEvent(&event) || continuer == 1)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            case SDLK_KP_2:
                SDL_RenderClear(renderer);
                char path[] = "img/yaniss(1).jpg";
                SDL_Rect dstrect = {0, 0, 255, 255};
                SDL_RenderCopy(renderer, loadImage(path, renderer), NULL, NULL);
                SDL_RenderPresent(renderer);
                break;
            case SDLK_KP_1:
            jouer(renderer);
                break;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
