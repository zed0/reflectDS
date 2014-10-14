#include "ball.hpp"

Ball::Ball(int id, int color, std::pair<int,int> position, std::pair<int, int> size)
{
	this->id = id;

	gfx = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxSub = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);
	for(int i=0; i<16*(16/2); ++i)
	{
		gfx[i] = color | (color<<8);
		gfxSub[i] = color | (color<<8);
	}

	this->position = position;
	this->size = size;
	this->velocity = {0,0};
}

void Ball::draw()
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
		SpriteSize_16x16,
		SpriteColorFormat_256Color, 
		graphic,          //pointer to the loaded graphics
		0,                //sprite rotation/scale matrix index 
		false,            //double the size when rotating?
		false,            //hide the sprite?
		false, false,     //vflip, hflip
		false             //apply mosaic
	);
}

void Ball::tick(int time)
{
	//std::pair<int, int> screenSize = {256, 192};
	std::pair<int, int> screenSize = {256, 384}; //screen height doubled to account for two screens
	position.first += velocity.first*time;
	position.second += velocity.second*time;

	if(position.first < 0)
	{
		position.first = -position.first;
		velocity.first = -velocity.first;
	}
	if(position.first + size.first > screenSize.first)
	{
		position.first = screenSize.first - (screenSize.first - position.first);
		velocity.first = -velocity.first;
	}
	if(position.second < 0)
	{
		position.second = -position.second;
		velocity.second = -velocity.second;
	}
	if(position.second + size.second > screenSize.second)
	{
		position.second = screenSize.second - (screenSize.second - position.second);
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

std::pair<int, int> Ball::getPosition(side_t side)
{
	std::pair<int, int> sidePosition = position;
	switch(side)
	{
		case LEFT:
			sidePosition.second += size.second/2;
			break;
		case RIGHT:
			sidePosition.first += size.first;
			sidePosition.second += size.second/2;
			break;
		case TOP:
			sidePosition.first += size.first/2;
			break;
		case BOTTOM:
			sidePosition.first += size.first/2;
			sidePosition.second += size.second;
			break;
	}
	return sidePosition;
}
