#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma region HEAD
#pragma region DESCRIPTION

/* light SDL2 template
 * DeCasteljau Subdivision
 * cubic bezier curves
 * http://www.cubic.org/docs/bezier.htm
 */

/* DEFINED PROGRESS GOALS
 * connect 4 points with 3 lines
 * 
 */
#pragma endregion DESCRIPTION

#pragma region INCLUDES
//system headers
#include <math.h>
//local headers
#include "helper.h"
#include <SDL2/SDL2_gfxPrimitives.h>

#pragma endregion INCLUDES

#pragma region CPP DEFINITIONS
#define WHITE 255, 255, 255, 255
#define BLACK 0, 0, 0, 255
#define RED 255, 0, 0, 255
#define WW 550
#define WH (WW / 16) * 12
#define POINTS 4
#pragma endregion CPP DEFINITIONS

#pragma region DATASTRUCTURES
SDL_Point points[POINTS];
struct fpoint
{
	float x;
	float y;
};
void round_points(SDL_Point *ipoint, struct fpoint *fpoint);
void lerp(struct fpoint *dest, struct fpoint *a, struct fpoint *b, float t);
void bezier(struct fpoint *dest, struct fpoint *a, struct fpoint *b, struct fpoint *c, struct fpoint *d, float t);
#pragma endregion DATASTRUCTURES

#pragma region GLOBALS
int ww = WW;
int wh = WH;

#pragma region VISIBLES
SDL_Surface *temp_surface = NULL;

SDL_Texture *logo = NULL;
SDL_Rect logo_dst;
#pragma endregion VISIBLES

SDL_Point mouse;

#pragma endregion GLOBALS

#pragma region FUNCTION PROTOTYPES
void assets_in(void);
void assets_out(void);
#pragma endregion FUNCTION PROTOTYPES

#pragma endregion HEAD

#pragma region MAIN FUNCTION
int main(int argc, char *argv[])
{

	(void)argc;
	(void)argv;

#pragma region INIT
	init();
	assets_in();

#pragma region WINDOW
	SDL_SetWindowPosition(Window, 0, 0);
	SDL_SetWindowSize(Window, ww, wh);
	SDL_SetWindowTitle(Window, "SDL2 Template");
	SDL_ShowWindow(Window);
#pragma endregion WINDOW

	// int r=255,g=0,b=0,a=255;
	points[0].x = 40;
	points[0].y = WH / 2;

	points[1].x = 142;
	points[1].y = 55;
	points[2].x = 372;
	points[2].y = 334;
	points[3].x = WW - 40;
	points[3].y = 160;

	// struct fpoint pa = { 40, 100 };
	// struct fpoint pb = { 80, 20  };
	// struct fpoint pc = { 150, 180 };
	// struct fpoint pd = { 260, 100 };

	struct fpoint fpoints[4];

	for (int i = 0; i < POINTS; i++)
	{
		round_points(&points[i], &fpoints[i]);
	}
	// SDL_SetRenderDrawColor(Renderer, RED);
	// for (int i=0; i<1000; ++i)
	// {
	// 	struct fpoint pp;
	// 	float t = ( (float)i/999.0);
	// 	bezier(&pp,&pa,&pb,&pc,&pd,t);
	// 	printf("%f %f\n", pp.x, pp.y);
	// 	SDL_RenderDrawPoint(Renderer,roundf(pp.x),roundf(pp.y));
	//
	// }

	SDL_Event event;
	int running = 1;
#pragma endregion INIT

#pragma region MAIN LOOP
	while (running)
	{

#pragma region EVENT LOOP
		SDL_GetMouseState(&mouse.x, &mouse.y);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = 0;
			}
			if (event.type == SDL_MOUSEMOTION)
			{
				// 			SDL_Log("x:%d y:%d",mouse.x, mouse.y);
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_RIGHT)
				{
					;
				}
				if (event.button.button == SDL_BUTTON_MIDDLE)
				{
					;
				}
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					;
				}
			}
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					running = 0;
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
#pragma endregion EVENT LOOP
#pragma region RENDERING
		SDL_SetRenderDrawColor(Renderer, WHITE);
		SDL_RenderClear(Renderer);

		SDL_RenderCopy(Renderer, logo, NULL, &logo_dst);

		for (int i = 0; i < POINTS; i++)
		{
			aacircleRGBA(Renderer, points[i].x, points[i].y, 4, RED);
			if (i < POINTS - 1)
				aalineRGBA(Renderer, points[i].x, points[i].y,
									 points[i + 1].x, points[i + 1].y, RED);
		}
		SDL_SetRenderDrawColor(Renderer, BLACK);
		for (int i = 0; i < 1000; ++i)
		{
			struct fpoint pp;
			float t = ((float)i / 999.0);

			bezier(&pp, &fpoints[0], &fpoints[1], &fpoints[2], &fpoints[3], t);
			// 		printf("%f %f\n", pp.x, pp.y);
			SDL_RenderDrawPoint(Renderer, roundf(pp.x), roundf(pp.y));
		}

		SDL_RenderPresent(Renderer);
#pragma endregion RENDERING
	}
#pragma endregion MAIN LOOP

	assets_out();
	exit_();
	return EXIT_SUCCESS;
}
#pragma endregion MAIN FUNCTION

#pragma region FUNCTIONS
void assets_in(void)
{

#pragma region LOGO
	temp_surface = IMG_Load("./assets/gfx/logo.png");
	logo = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(logo, NULL, NULL, &logo_dst.w, &logo_dst.h);
	logo_dst.x = (ww / 2) - (logo_dst.w / 2);
	logo_dst.y = (wh / 2) - (logo_dst.h / 2);
#pragma endregion LOGO
}

void assets_out(void)
{
	SDL_DestroyTexture(logo);
}

void bezier(struct fpoint *dest, struct fpoint *a, struct fpoint *b, struct fpoint *c, struct fpoint *d, float t)
{
	struct fpoint ab, bc, cd, abbc, bccd;
	lerp(&ab, a, b, t);					 // point between a and b (green)
	lerp(&bc, b, c, t);					 // point between b and c (green)
	lerp(&cd, c, d, t);					 // point between c and d (green)
	lerp(&abbc, &ab, &bc, t);		 // point between ab and bc (blue)
	lerp(&bccd, &bc, &cd, t);		 // point between bc and cd (blue)
	lerp(dest, &abbc, &bccd, t); // point on the bezier-curve (black)
}
// simple linear interpolation between two points
void lerp(struct fpoint *dest, struct fpoint *a, struct fpoint *b, float t)
{
	dest->x = a->x + (b->x - a->x) * t;
	dest->y = a->y + (b->y - a->y) * t;
}
void round_points(SDL_Point *ipoint, struct fpoint *fpoint)
{
	fpoint->x = roundf(ipoint->x);
	fpoint->y = roundf(ipoint->y);
}
#pragma endregion FUNCTIONS
