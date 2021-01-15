#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "renderwindow.h"
#include "logic.h"

#define FPS 60
#define SIZEX 30
#define SIZEY 20

RenderWindow window;
std::vector<SDL_Texture*> tileSprites;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
enum{menu, game, end} loop;
bool gameRunning;
Grid grid;
snake snek;
std::vector<SDL_Texture*> title;

void init(){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	gameRunning = 1;
	window.create("snek", SCREEN_WIDTH, SCREEN_HEIGHT);
	snek.init(SIZEX,SIZEY);
	grid = window.createGrid(SIZEX,SIZEY);
	tileSprites.push_back(window.loadTexture("empty.png"));
	tileSprites.push_back(window.loadTexture("head.png"));
	tileSprites.push_back(window.loadTexture("tail.png"));
	tileSprites.push_back(window.loadTexture("apple.png"));
	//SDL_SetTextureColorMod(test, 255, 10, 10);
	//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	srand((unsigned)time(0));
}


void eventLoop(){
	SDL_Event event;
 	while (SDL_PollEvent(&event))
 	{
		switch (event.type) {
			case SDL_QUIT:{
					gameRunning=0;
		  		break;
			}
			case SDL_MOUSEBUTTONDOWN:{
				if(loop != game){
					loop = game;
				}
				else{
				//	if(event.button.button == SDL_BUTTON_LEFT)
				//		window.renderGrid(0,0, &grid, 0,100,255);
				}
			}
			case SDL_KEYDOWN:{
				switch (event.key.keysym.sym) {
					case SDLK_a:
						snek.setDirection(std::make_pair(-1,0));
						break;
					case SDLK_d:
						snek.setDirection(std::make_pair(1,0));
						break;
					case SDLK_w:
						snek.setDirection(std::make_pair(0,-1));
						break;
					case SDLK_s:
						snek.setDirection(std::make_pair(0,1));
						break;
				}
			}

			case SDL_WINDOWEVENT:{
				//levelGrid = window.createGrid(4,3);
				grid = window.createGrid(SIZEX, SIZEY, 1.0);
		  	break;
			}
		}
	}
}
void drawBoard(){
	SDL_Rect src;
	src = grid.getSize();
	window.drawRect(100,100,100,&src);
	src.x = 0, src.y = 0, src.w = 16, src.h = 16;
	for(int x=0; x<SIZEX; x++){
		for(int y=0; y<SIZEY; y++){
			//printf("%d\n", snek.getXY(x,y));
			window.renderGrid(x,y,tileSprites[snek.getXY(x,y)], &grid, src);
			//window.renderGrid(x,y,tileSprites[1], &grid, src);
		}
	}
}

int main(int argc, char* args[]){
	init();
	loop = menu;
	unsigned int time=0;
	while(gameRunning){
		while(loop == menu && gameRunning){
			eventLoop();
			SDL_Delay(int(1000/FPS)); //delay
			window.clear();
			window.display();
		}
		while(loop == game && gameRunning){
			//printf("xd");
			window.clear(50,50,50);
			eventLoop();
			if(SDL_GetTicks()-time > 200){
				time = SDL_GetTicks();
				gameRunning &= snek.update();
			}
			drawBoard();
			SDL_Delay(int(1000/FPS)); //delay
			window.display();
		}
	}
	window.cleanUp();
	SDL_Quit();
	return 0;
}
