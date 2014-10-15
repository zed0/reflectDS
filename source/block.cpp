#include "block.hpp"

Block::Block(int id, int color, std::pair<int,int> position, std::pair<int,int> size)
{
	this->id = id;

	gfx = oamAllocateGfx(&oamMain, SpriteSize_32x16, SpriteColorFormat_256Color);
	gfxSub = oamAllocateGfx(&oamSub, SpriteSize_32x16, SpriteColorFormat_256Color);
	for(int i=0; i<32*(16/2); ++i)
	{
		gfx[i] = color | (color<<8);
		gfxSub[i] = color | (color<<8);
	}

	this->position = position;
	this->size = size;
	this->destroyed = false;
}

void Block::draw()
{
	auto screen = &oamMain;
	std::pair<int, int> graphicPosition = position;
	auto graphic = gfx;
	//Check which screen the ball is on:
	if(position.second <= 192)
	{
		//Main screen
		screen = &oamMain;
	}
	else
	{
		//Sub screen
		screen = &oamSub;
		graphicPosition.second -= 192;
		graphic = gfxSub;
	}
	oamSet(screen,      //main graphics engine context
		id,               //oam index (0 to 127)  
		graphicPosition.first, graphicPosition.second, //x and y pixel location of the sprite
		0,                //priority, lower renders last (on top)
		1,                //this is the palette index if multiple palettes or the alpha value if bmp sprite
		SpriteSize_32x16,
		SpriteColorFormat_256Color, 
		graphic,          //pointer to the loaded graphics
		0,                //sprite rotation/scale matrix index 
		false,            //double the size when rotating?
		destroyed,        //hide the sprite?
		false, false,     //vflip, hflip
		false             //apply mosaic
	);
}

//simple check whether point is inside rectangle
bool Block::getCollision(std::pair<int, int> point)
{
	if(destroyed)
	{
		return false;
	}
	if(
			point.first > position.first && point.first < position.first + size.first &&
			point.second > position.second && point.second < position.second + size.second
	  )
	{
		return true;
	}
	return false;
}

void Block::setPosition(std::pair<int, int> position)
{
	this->position = position;
}
