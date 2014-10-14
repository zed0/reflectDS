#include "ball.hpp"

Ball::Ball(int id, int color, std::pair<int,int> position, std::pair<int, int> size)
{
	this->id = id;

	gfx = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	for(int i=0; i<16*(16/2); ++i)
	{
		gfx[i] = color | (color<<8);
	}

	this->position = position;
	this->size = size;
	this->velocity = {0,0};
}

void Ball::draw()
{
	oamSet(&oamMain,      //main graphics engine context
		id,                //oam index (0 to 127)  
		position.first, position.second,             //x and y pixel location of the sprite
		0,                //priority, lower renders last (on top)
		1,                //this is the palette index if multiple palettes or the alpha value if bmp sprite
		SpriteSize_16x16,
		SpriteColorFormat_256Color, 
		gfx,              //pointer to the loaded graphics
		0,                //sprite rotation/scale matrix index 
		false,            //double the size when rotating?
		false,            //hide the sprite?
		false, false,     //vflip, hflip
		false             //apply mosaic
	);
}

void Ball::tick(int time)
{
	auto originalPosition = position;
	position.first += velocity.first*time;
	position.second += velocity.second*time;

	if(position.first < 0)
	{
		position.first = -position.first;
		velocity.first = -velocity.first;
	}
	if(position.first + size.first > 256) //screen width = 256
	{
		position.first = 256 - (256 - position.first);
		velocity.first = -velocity.first;
	}
	if(position.second < 0)
	{
		position.second = -position.second;
		velocity.second = -velocity.second;
	}
	if(position.second + size.second > 192) //screen height = 192
	{
		position.second = 192 - (192 - position.second);
		velocity.second = -velocity.second;
	}
}

void Ball::setVelocity(std::pair<int, int> velocity)
{
	this->velocity = velocity;
}

std::pair<int, int> Ball::getVelocity()
{
	return velocity;
}
