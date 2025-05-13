#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "game.h"

//ligne de compilation gcc main.c file.c game.c event.c charactere.c -o mario -lSDL2main -lSDL2_image -lSDL2

void init(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture, int w, int h);
void end_game(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture);

int main(int argc, char *argv[])
{
	SDL_Window *menu = NULL; // Fenêtre menu
	SDL_Renderer *renderer_menu = NULL; // renderer menu
	SDL_Texture *img_menu = NULL; // Texture menu
	SDL_Event event;
	bool done = false;
	init(&menu, &renderer_menu, &img_menu, LARGEUR_FENETRE, HAUTEUR_FENETRE);
	while((!done) && SDL_WaitEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				done = true;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_1:
					case SDLK_KP_1:
						SDL_Log("1 Pressé");
						SDL_DestroyTexture(img_menu);
						jouer(renderer_menu);
						done = true;
						break;
					case SDLK_2:
					case SDLK_KP_2:
						SDL_Log("2 Pressé");
						SDL_RenderClear(renderer_menu);
						SDL_Texture *texture = loadImage("./img/credit.png", renderer_menu);
						SDL_RenderCopy(renderer_menu, texture, NULL, NULL);
						SDL_RenderPresent(renderer_menu);
						break;
					case SDLK_ESCAPE:
						done = true;
						break;
					default:
						break;
				}
			default:
				break;
		}
	}
	end_game(menu, renderer_menu, img_menu);

	return 0;
}

void init(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture, int w, int h){
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_Log("Erreur initialisation SDL: ");
		exit(0);
	}
	*window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	if(window == NULL){
		SDL_Log("Erreur initialisation menu: ");
		SDL_Quit();
		exit(0);
	}
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
		SDL_Log("Erreur loadimage: ");
		SDL_DestroyWindow(*window);
		SDL_Quit();
		exit(0);
	}
	*texture = loadImage("./img/menu.jpg", *renderer);
	SDL_RenderCopy(*renderer, *texture, NULL, NULL);
	SDL_RenderPresent(*renderer);
}

void end_game(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture){
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
