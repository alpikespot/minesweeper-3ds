#include <3ds.h>
#include <citro2d.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <chrono>
#define BOTTOM_SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define TOP_SCREEN_WIDTH  400
#define D_DOWN 7
#define D_UP 6
#define D_RIGHT 4
#define D_LEFT 5
using namespace std;
int main(int argc, char* argv[])
{
	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	//consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_RIGHT);
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_RIGHT);

	// Define colors
	u32 clrRec1 = C2D_Color32(100, 0,0,255);
	u32 clrClear = C2D_Color32(0,0,0,0);
	u32 clrRecPress = C2D_Color32(255,0,0,255);
	int tSize = 20;
	u32 clr;
	int xpos = 0;
	int ypos = 0;
	float oldTime; float currentTime; float deltaTime;
	TickCounter tick;
	consoleInit(GFX_TOP, NULL);
	int ticks=0;
	float bPressT[32] = {0};
	bool bPressed[32] = {false};
	const int tileNumX = 16;
	const int tileNumY = 12;
	while (aptMainLoop())
	{

		hidScanInput();
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START) break; // break in order to return to hbmenu
		touchPosition touch;
		hidTouchRead(&touch);//Read the touch screen coordinates 

		u32 kHeld = hidKeysHeld();
		u32 kUp = hidKeysUp();
		for (int i=0;i<32;i++){
			if ((kHeld) & BIT(i)){
				bPressT[i] += 1;
			}
			else {
				bPressT[i] = 0;
			}
		}

			if ((kDown & BIT(D_UP)) || (bPressT[D_UP]>40 && ticks%2==0)){ 
				ypos -= 1;
			}
			else if ((kDown & BIT(D_DOWN)) || (bPressT[D_DOWN]>40 && ticks%2==0)){
				ypos += 1;
			}
			else if (((kDown & BIT(D_RIGHT)) || (kDown & BIT(8))) || (bPressT[D_RIGHT]>40 && ticks%2==0)){
				xpos += 1;
			}
			else if (((kDown & BIT(D_LEFT))|| (kDown & BIT(9))) || (bPressT[D_LEFT]>40 && ticks%2==0)){
				xpos -= 1;
			}
			xpos = C2D_Clamp(xpos, 0, int(BOTTOM_SCREEN_WIDTH/tSize)-1);
			ypos = C2D_Clamp(ypos, 0, int(SCREEN_HEIGHT/tSize)-1);

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			//--Draw TOP Screen--
			printf("%f \n", bPressT[D_DOWN]);
			/*
			C2D_TargetClear(top, clrClear);
			C2D_SceneBegin(top);
			C2D_DrawRectSolid(xpos*tSize+1, ypos*tSize+1,0, tSize-2, tSize-2, clrRec1);*/

			//--Draw BOTTOM screen--
			C2D_TargetClear(bottom, clrClear);
			C2D_SceneBegin(bottom);
			C2D_DrawRectSolid(1, 1, 0, tSize-2, tSize-2, clrRec1);
			for (int y=0;y<tileNumY;y++){ for (int x=0;x<tileNumX;x++){
				
					if (x == int(xpos) && y == int(ypos)) //&& (kDown & BIT(20)))
					{clr = clrRecPress;}
					else{clr = clrRec1;}
					C2D_DrawRectSolid(x*tSize+1, y*tSize+1, 0, tSize-2, tSize-2, clr);
					//C2D_Color32(rand()%255,0,0,255)
				} }

			//printf("\x1b[2;0H%03d; %03d", touch.px, touch.py);

		C3D_FrameEnd(0);
		ticks++;

		
	}

	gfxExit();
	return 0;
}
/*
for (int y=0;y<SCREEN_HEIGHT;y=y+tSize){
				for (int x=0;x<SCREEN_WIDTH;x=x+tSize){
					if (int(x/tSize) == int(touch.px/tSize) && int(y/tSize) == int(touch.py/tSize))
					{
						clr = clrRecPress;
					}
					else{
						clr = clrRec1;
					}
					C2D_DrawRectSolid(x+1, y+1, 0, tSize-2, tSize-2, clr);
					//C2D_Color32(rand()%255,0,0,255)
				}
			}
			*/