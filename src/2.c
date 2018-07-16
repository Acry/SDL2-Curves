//BEGIN HEAD
//BEGIN DESCRIPTION

/* light SDL2 template
 * DeCasteljau Subdivision
 * 
 */

/* DEFINED PROGRESS GOALS
 * connect 4 points with 3 lines
 * 
 */
//END   DESCRIPTION

//BEGIN INCLUDES
//system headers
#include <math.h>
//local headers
#include "helper.h"
#include <SDL2/SDL2_gfxPrimitives.h>

//END   INCLUDES

//BEGIN CPP DEFINITIONS
#define WHITE 255,255,255,255
#define BLACK 0,0,0,255
#define RED   255,0,0,255
#define WW 550
#define WH (WW/16)*12
#define POINTS 4
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
SDL_Point points[POINTS];
struct fpoint
{
	float x;
	float y;
};
void lerp(struct fpoint *dest, struct fpoint *a,  struct fpoint *b,  float t);
void bezier(struct fpoint *dest, struct fpoint * a, struct fpoint * b, struct fpoint * c, struct fpoint * d, float t);
//END	DATASTRUCTURES

//BEGIN GLOBALS
int ww=WW;
int wh=WH;

//BEGIN VISIBLES
SDL_Surface    *temp_surface	= NULL;

SDL_Texture    *logo		= NULL;
SDL_Rect 	logo_dst;
//END 	VISIBLES

SDL_Point	mouse;

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
void assets_in	(void);
void assets_out	(void);
//END	FUNCTION PROTOTYPES

//END 	HEAD

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{

(void)argc;
(void)argv;

//BEGIN INIT
init();
assets_in();

//BEGIN WINDOW
SDL_SetWindowPosition(Window,0,0);
SDL_SetWindowSize(Window,ww,wh);
SDL_SetWindowTitle(Window, "SDL2 Template");
SDL_ShowWindow(Window);
//END WINDOW

// int r=255,g=0,b=0,a=255;
// points[0].x=40;
// points[0].y=WH/2;
// 
// points[1].x=142;
// points[1].y=55;
// points[2].x=372;
// points[2].y=334;
// points[3].x=WW-40;
// points[3].y=160;

struct fpoint pa = { 40, 100 };
struct fpoint pb = { 80, 20  };
struct fpoint pc = { 150, 180 };
struct fpoint pd = { 260, 100 };
SDL_SetRenderDrawColor(Renderer, RED);
for (int i=0; i<1000; ++i)
{
	struct fpoint pp;
	float t = ( (float)i/999.0);
	bezier(&pp,&pa,&pb,&pc,&pd,t);
	printf("%f %f\n", pp.x, pp.y);
	SDL_RenderDrawPoint(Renderer,roundf(pp.x),roundf(pp.y));

}

SDL_Event event;
int running = 1;
//END   INIT

//BEGIN MAIN LOOP
while(running){

	//BEGIN EVENT LOOP
	SDL_GetMouseState(&mouse.x, &mouse.y);
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running =0;
		}
		if(event.type == SDL_MOUSEMOTION){
			SDL_Log("x:%d y:%d",mouse.x, mouse.y);
		}
		if(event.type == SDL_MOUSEBUTTONDOWN){
			if(event.button.button == SDL_BUTTON_RIGHT){
				;
			}
			if(event.button.button == SDL_BUTTON_MIDDLE){
				;
			}
			if(event.button.button==SDL_BUTTON_LEFT){
				;
			}
		}
		if(event.type == SDL_KEYDOWN ){
			switch(event.key.keysym.sym ){
				case SDLK_ESCAPE:
					running =0;
					break;

				case SDLK_r:
				case SDLK_BACKSPACE:
					break;

				case SDLK_p:	
				case SDLK_SPACE:
					break;
					
				default:
					break;
			}
		}
	}
	//END   EVENT LOOP
	//BEGIN RENDERING
// 	SDL_SetRenderDrawColor(Renderer, WHITE);
// 	SDL_RenderClear(Renderer);

// 	SDL_RenderCopy(Renderer, logo, NULL, &logo_dst);

// 	for ( int i=0; i<POINTS; i++){
// 		aacircleRGBA(Renderer, points[i].x, points[i].y, 4, r,g,b,a);
// 		if (i<POINTS-1)
// 		aalineRGBA(Renderer, points[i].x, points[i].y,
// 			   points[i+1].x, points[i+1].y, r,g,b,a);
// 	}
	
	
	
	SDL_RenderPresent(Renderer);
	//END   RENDERING
}
//END   MAIN LOOP

assets_out();
exit_();
return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS
void assets_in(void)
{

	//BEGIN LOGO
	temp_surface = IMG_Load("./assets/gfx/logo.png");
	logo = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(logo, NULL, NULL, &logo_dst.w, &logo_dst.h);
	logo_dst.x=(ww/2)-(logo_dst.w/2);
	logo_dst.y=(wh/2)-(logo_dst.h/2);
	//END 	LOGO

}

void assets_out(void)
{
	SDL_DestroyTexture(logo);
}

void bezier(struct fpoint *dest, struct fpoint *a, struct fpoint *b, struct fpoint *c, struct fpoint *d, float t)
{
	struct fpoint ab,bc,cd,abbc,bccd;
	lerp(&ab, a,b,t);           // point between a and b (green)
	lerp(&bc, b,c,t);           // point between b and c (green)
	lerp(&cd, c,d,t);           // point between c and d (green)
	lerp(&abbc, &ab,&bc,t);       // point between ab and bc (blue)
	lerp(&bccd, &bc,&cd,t);       // point between bc and cd (blue)
	lerp(dest, &abbc,&bccd,t);   // point on the bezier-curve (black)
}
// simple linear interpolation between two points
void lerp(struct fpoint *dest, struct fpoint *a, struct fpoint *b, float t)
{
	dest->x = a->x + (b->x-a->x)*t;
	dest->y = a->y + (b->y-a->y)*t;
}
//END   FUNCTIONS
