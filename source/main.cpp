#include <3ds.h>
#include <citro2d.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOTTOM_SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define TOP_SCREEN_WIDTH  400
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
	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START) break; // break in order to return to hbmenu
		touchPosition touch;
		hidTouchRead(&touch);//Read the touch screen coordinates 

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			//--Draw TOP Screen--
			C2D_TargetClear(top, clrClear);
			C2D_SceneBegin(top);
			C2D_DrawRectSolid(1, 1, 0, tSize-2, tSize-2, clrRec1);

			for (int y=0;y<SCREEN_HEIGHT;y=y+tSize){
				for (int x=0;x<TOP_SCREEN_WIDTH;x=x+tSize){
					if (int(x/tSize) == int(touch.px/tSize) && int(y/tSize) == int(touch.py/tSize))
					{
						clr = clrRecPress;
					}
					else{
						clr = clrRec1;
					}
					C2D_DrawRectSolid(x+1, y+1, 0, tSize-2, tSize-2, C2D_Color32(rand()%255,0,0,255));
				}
			}

			//--Draw BOTTOM screen--
			C2D_TargetClear(bottom, clrClear);
			C2D_SceneBegin(bottom);
			C2D_DrawRectSolid(1, 1, 0, tSize-2, tSize-2, clrRec1);

			for (int y=0;y<SCREEN_HEIGHT;y=y+tSize){
				for (int x=0;x<BOTTOM_SCREEN_WIDTH;x=x+tSize){
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

			//printf("\x1b[2;0H%03d; %03d", touch.px, touch.py);

		C3D_FrameEnd(0);


		
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