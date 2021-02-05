
#include "main.h"

void destroy();
void init_window();
void Close();

void rectangleBoundsMouseOver(int x,int y,int w,int h,Uint8 r,Uint8 g,Uint8 b,Uint8 a,bool hover);

// each pixel stores rgba data
// init all pixels to white
// if you click a pixel the current color is added to that pixel

int main(int argc, char* args[])
{
	init_window();
	
	Region r =  {0,0,10,10};
	enum {color1, color2, color3, color4}; int currentcolor = color1;
	enum {p1,p2,p3,p4};                    int pixel        = p1;
	
	while(running){

		//INPUT
		while(POLLEVENT){
			if(QUIT){ exit(0); }
			
			if(DOWNPRESS){ if(ESCAPE){exit(0);} }
			
			if(MOUSEBUTTONDOWN)
			{
				
				int posx = 60, posy = 60; //CANVAS
				/**/
				for(int i = 0; i < 8; i++)
				{
					for(int j = 0; j < 8; j++)
					{
						if(currentcolor == color1)
						{
							if(MX(0+((posx+1)*i),0+((posx+1)*j), posx,posy))
							{
								pixel = p1;
							}
						}
					}
				}
		
				posx = 30;
				posy = 30;
				for(int i = 0; i < 3; i++) //TOOLBOX
				{
					for(int j = 0; j < 12; j++)
					{
						if(MX(500+((posx+1)*i),0+((posx+1)*j), posx,posy))
						{
							
						}
					}
				}
				
				posx = 30, posy = 30; //PALLETE
				for(int i = 0; i < 19; i++)
				{
					for(int j = 0; j < 3; j++)
					{
						if(MX(0+((posx+1)*i),500+((posx+1)*j), posx,posy))
						{
							CC(0,0,color1)
							CC(1,0,color2)
							CC(2,0,color3)
							CC(3,0,color4)
						}
					}
				}
			}
		}
		printf("%i\n",currentcolor);

		//DRAW
		SDL_SetRenderDrawColor(renderer,BLACK);
		SDL_RenderClear(renderer);

		int posx = 60, posy = 60; //CANVAS
      /**/
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				if(i == 2 && j == 3)
				{
					if     (currentcolor == color1){drawFillRect(renderer, 0+((posx+1)*i),0+((posx+1)*j), posx,posy,PEACH);}
					else if(currentcolor == color1){drawFillRect(renderer, 0+((posx+1)*i),0+((posx+1)*j), posx,posy,PEACH);}
					else{drawFillRect(renderer, 0+((posx+1)*i),0+((posx+1)*j), posx,posy,MAROON);}
				}
				else
				{
					drawFillRect(renderer, 0+((posx+1)*i),0+((posx+1)*j), posx,posy,MAROON);
				}
				rectangleBoundsMouseOver(0+((posx+1)*i),0+((posx+1)*j), posx,posy,MAGENTA,1);
			}
		}
		posx = 30;
		posy = 30;
		for(int i = 0; i < 3; i++) //TOOLBOX
		{
			for(int j = 0; j < 12; j++)
			{
				drawFillRect(renderer,   500+((posx+1)*i),0+((posx+1)*j), posx,posy,CYAN);
				rectangleBoundsMouseOver(500+((posx+1)*i),0+((posx+1)*j), posx,posy,MAGENTA,1);
			}
		}
		/**/
		posx = 30;
		posy = 30;
		for(int i = 0; i < 19; i++) //PALLETTE
		{
			for(int j = 0; j < 3; j++)
			{
				if     (i == 0 && j == 0){drawFillRect(renderer,   0+((posx+1)*i),500+((posx+1)*j), posx,posy,WHITE);}
				else if(i == 1 && j == 0){drawFillRect(renderer,   0+((posx+1)*i),500+((posx+1)*j), posx,posy,BLUE);}
				else if(i == 2 && j == 0){drawFillRect(renderer,   0+((posx+1)*i),500+((posx+1)*j), posx,posy,PURPLE);}
				else if(i == 3 && j == 0){drawFillRect(renderer,   0+((posx+1)*i),500+((posx+1)*j), posx,posy,CYAN);}
				else{drawFillRect(renderer,   0+((posx+1)*i),500+((posx+1)*j), posx,posy,WHITE);}
				rectangleBoundsMouseOver(0+((posx+1)*i),500+((posx+1)*j), posx,posy,MAGENTA,1);
			}
		}
		
		/**/
		if     (currentcolor == color1){ drawFillRect(renderer, 500,400, 80,80, WHITE);}
		else if(currentcolor == color2){ drawFillRect(renderer, 500,400, 80,80, BLUE);}
		else if(currentcolor == color3){ drawFillRect(renderer, 500,400, 80,80, PURPLE);}
		else if(currentcolor == color4){ drawFillRect(renderer, 500,400, 80,80, CYAN);}
		else{drawFillRect(renderer,   500,400, 80,80,WHITE);}
		rectangleBoundsMouseOver(500,400, 80,80,MAGENTA,1);

		/**/
		
		Sleep(1000/20);
		SDL_RenderPresent(renderer);
	}
	
	Close();
	return(0);
}

void rectangleBoundsMouseOver(int x,int y,int w,int h,Uint8 r,Uint8 g,Uint8 b,Uint8 a,bool hover){
	
	int mx, my;
	bool drawfilltrue = false;

	SDL_GetMouseState(&mx,&my);
	
	if(mx>=x && my>=y && mx<=w+x && my<=h+y){
		drawfilltrue = true;
	}else{
		drawfilltrue = false;
	}

	if(drawfilltrue && hover){
		drawFillRect(renderer,x,y,w,h,r,g,b,a);
	}
	else{
		drawOutlineRect(renderer,x,y,w,h,r,g,b,a);
	}
}

void init_window()
{
	{
		if(SDL_Init(SDL_INIT_VIDEO) < 0){
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		}else{
			assert(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"));
			window = SDL_CreateWindow(
				"SDL Tutorial",
				400,
				200,
				600,
				600,
				SDL_WINDOW_SHOWN);

			if(window == NULL){
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			}else{
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
				if(renderer == NULL){
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				}else{
					SDL_SetRenderDrawColor(renderer, WHITE);
					
					//Initialize PNG Loading
					int imgFlags = IMG_INIT_PNG;
					if( !( IMG_Init( imgFlags ) & imgFlags )){
						printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					}
				}
			}
		}
	}
	
	#if 0
	SDL_SetWindowFullscreen(gWindow,SDL_WINDOW_FULLSCREEN);
	#endif
}

void Close(){

	//Free loaded image

	//Destroy window
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystem
	SDL_Quit();
}

