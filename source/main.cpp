#include <nds.h>

#include <vector>
#include <iostream>
#include <algorithm>

#include "block.hpp"
#include "ball.hpp"

//screen size: 256 × 192

int main(void) {
	//initialise both screens to display 2D sprites:
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_SPRITE);
	//vramSetBankC(VRAM_C_SUB_BG);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	oamInit(&oamMain, SpriteMapping_1D_32, false);
	oamInit(&oamSub, SpriteMapping_1D_32, false);

	//consoleDemoInit(); //Uncomment for debugging

	//set up palette colors:
	SPRITE_PALETTE[0] = RGB15( 0, 0, 0); //black
	SPRITE_PALETTE[1] = RGB15( 0, 0,31); //blue
	SPRITE_PALETTE[2] = RGB15( 0,31, 0); //green
	SPRITE_PALETTE[3] = RGB15( 0,31,31); //cyan
	SPRITE_PALETTE[4] = RGB15(31, 0, 0); //red
	SPRITE_PALETTE[5] = RGB15(31, 0,31); //magenta
	SPRITE_PALETTE[6] = RGB15(31,31, 0); //yellow
	SPRITE_PALETTE[7] = RGB15(31,31,31); //white

	SPRITE_PALETTE_SUB[0] = RGB15( 0, 0, 0); //black
	SPRITE_PALETTE_SUB[1] = RGB15( 0, 0,31); //blue
	SPRITE_PALETTE_SUB[2] = RGB15( 0,31, 0); //green
	SPRITE_PALETTE_SUB[3] = RGB15( 0,31,31); //cyan
	SPRITE_PALETTE_SUB[4] = RGB15(31, 0, 0); //red
	SPRITE_PALETTE_SUB[5] = RGB15(31, 0,31); //magenta
	SPRITE_PALETTE_SUB[6] = RGB15(31,31, 0); //yellow
	SPRITE_PALETTE_SUB[7] = RGB15(31,31,31); //white

	//create our game objects:
	Ball ball(0, 4, {20, 50}, {16, 16});
	ball.setVelocity({1,1});
	//Block paddle(1, 5, {50, 300}, {32,16});
	std::vector<Block> blocks;
	for(int i=0; i<20; ++i)
	{
		std::pair<int, int> size = {32,16};
		std::pair<int, int> position = {(i%10)*size.first,(i/10)*size.second};
		Block currentBlock(i+2, (i%7)+1, position, size);
		blocks.push_back(currentBlock);
	}

	touchPosition touch;
	while(true)
	{
		//check for input:
		scanKeys();
		int held = keysHeld();
		touchRead(&touch);
		if(held & KEY_TOUCH)
		{
			/*
			for(int i=-10; i<10; ++i)
			{
				for(int j=-10; j<10; ++j)
				{
					VRAM_C[touch.px+i+(touch.py+j)*SCREEN_WIDTH] = rand();
				}
			}
			*/
			//paddle.setPosition({touch.px, 192+touch.py});
		}

		//do engine updates:
		ball.tick(1);
		for(auto & block: blocks)
		{
			ball.collide(block);
		}
		//ball.collide(paddle);
		//paddle.destroyed = false;

		//draw to buffer:
		for(auto & block : blocks)
		{
			block.draw();
		}
		ball.draw();
		//paddle.draw();

		//wait for natural refresh rate:
		swiWaitForVBlank();
		//draw to screens:
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
		if(held & KEY_TOUCH)
		{
			for(int i=-10; i<10; ++i)
			{
				for(int j=-10; j<10; ++j)
				{
					VRAM_C[touch.px+i+(touch.py+j)*SCREEN_WIDTH] = rand();
				}
			}
			//paddle.setPosition({touch.px, 192+touch.py});
		}
	}

	return 0;
}
