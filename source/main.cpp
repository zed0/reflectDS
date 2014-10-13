
#include <nds.h>

#include <vector>
#include <iostream>

volatile int frame = 0;

void Vblank() {
	frame++;
}

void drawBlock(u16* gfx, int x, int y, int i);

int main(void) {

/*
	touchPosition touchXY;

	irqSet(IRQ_VBLANK, Vblank);

	consoleDemoInit();

	std::cout << __func__;
	std::vector<int> foo = {1,2,3,4,5};
	int total = 0;
	for(auto const& a : foo)
	{
		total+= a;
	}
	std::cout << total;

	while(1) {

		swiWaitForVBlank();
		touchRead(&touchXY);

		// print at using ansi escape sequence \x1b[line;columnH 
		std::cout << "\x1b[10;0HFrame = " << frame;
		std::cout << "\x1b[16;0HTouch x = " << touchXY.rawx << ", " << touchXY.px;
		std::cout << "Touch y = " << touchXY.rawy << ", " << touchXY.py;
	
	}
*/
	videoSetMode(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_SPRITE);
	oamInit(&oamMain, SpriteMapping_1D_32, false);
	std::vector<u16*> gfx(20);
	for(int i=0; i<gfx.size(); ++i)
	{
		gfx.at(i) = oamAllocateGfx(&oamMain, SpriteSize_32x16, SpriteColorFormat_256Color);
		for(int j=0; j<32*16/2; j++)
		{
			//fill sprite with color 1, 2 pixels at a time, thus the bit-shift
			gfx.at(i)[j] = ((i%7)+1) | (((i%7)+1)<<8);
		}
	}

	//set up palette colors:
	SPRITE_PALETTE[0] = RGB15( 0, 0, 0); //black
	SPRITE_PALETTE[1] = RGB15( 0, 0,31); //blue
	SPRITE_PALETTE[2] = RGB15( 0,31, 0); //green
	SPRITE_PALETTE[3] = RGB15( 0,31,31); //cyan
	SPRITE_PALETTE[4] = RGB15(31, 0, 0); //red
	SPRITE_PALETTE[5] = RGB15(31, 0,31); //magenta
	SPRITE_PALETTE[6] = RGB15(31,31, 0); //yellow
	SPRITE_PALETTE[7] = RGB15(31,31,31); //white

	while(true)
	{
		//scanKeys();
		for(int i=0; i<20; ++i)
		{
			drawBlock(gfx.at(i), 16*i, 16*i, i);
		}
		swiWaitForVBlank();
		oamUpdate(&oamMain);
	}

	return 0;
}

void drawBlock(u16* gfx, int x, int y, int i)
{
	oamSet(&oamMain,      //main graphics engine context
		i,                //oam index (0 to 127)  
		x, y,             //x and y pixel location of the sprite
		0,                //priority, lower renders last (on top)
		i,                //this is the palette index if multiple palettes or the alpha value if bmp sprite
		SpriteSize_32x16,
		SpriteColorFormat_256Color, 
		gfx,              //pointer to the loaded graphics
		0,                //sprite rotation/scale matrix index 
		false,            //double the size when rotating?
		false,            //hide the sprite?
		false, false,     //vflip, hflip
		false             //apply mosaic
	);
}
