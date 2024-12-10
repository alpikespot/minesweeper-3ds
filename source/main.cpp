#include <3ds.h>
#include <citro2d.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240
int main(int argc, char* argv[])
{
	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	// Define colors
	u32 clrRec1 = C2D_Color32(0x9A, 0x6C, 0xB9, 255);
	u32 clrClear = C2D_Color32(0,0,0,0);
	printf("%d\n");
	
	// Main loop
	while (aptMainLoop())
	{
		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, clrClear);
		C2D_SceneBegin(top);
		for (int y=0;y<SCREEN_HEIGHT;y=y+10){
			for (int x=0;x<SCREEN_WIDTH;x=x+10){
				C2D_DrawRectSolid(x+1, y+1, 0, 8, 8, C2D_Color32(rand()%255,0,0,255));
			}
		}
		C3D_FrameEnd(0);


		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu
	}

	gfxExit();
	return 0;
}
