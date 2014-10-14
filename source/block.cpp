#include "block.hpp"

Block::Block(int id, int color, int x, int y)
{
	this->id = id;

	gfx = oamAllocateGfx(&oamMain, SpriteSize_32x16, SpriteColorFormat_256Color);
	for(int i=0; i<32*(16/2); ++i)
	{
		gfx[i] = color | (color<<8);
	}

	this->x = x;
	this->y = y;
}

void Block::draw()
{
	oamSet(&oamMain,      //main graphics engine context
		id,                //oam index (0 to 127)  
		x, y,             //x and y pixel location of the sprite
		0,                //priority, lower renders last (on top)
		1,                //this is the palette index if multiple palettes or the alpha value if bmp sprite
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

//TODO:
int Block::getCollision()
{
	return 0;
}
