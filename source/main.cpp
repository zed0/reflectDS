#include <nds.h>

#include <vector>
#include <iostream>

#include "block.hpp"

int main(void) {
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_SPRITE);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	consoleDemoInit(); //for debugging
	oamInit(&oamMain, SpriteMapping_1D_32, false);
	std::vector<Block> blocks;
	for(int i=0; i<20; ++i)
	{
		Block currentBlock(i, i%8, i*16, i*16);
		blocks.push_back(currentBlock);
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
		for(auto & block : blocks)
		{
			block.draw();
		}
		swiWaitForVBlank();
		oamUpdate(&oamMain);
	}

	return 0;
}
