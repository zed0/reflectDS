#include "line.hpp"

Line::Line(std::pair<int, int> start, std::pair<int, int> end)
{
	this->start = start;
	this->end = end;
}

void Line::drawPixel(std::pair<int,int> position, int background, int color)
{
	int pixValue;
	if(position.first%2)
	{
		pixValue = color<<8;
	}
	else
	{
		pixValue = color;
	}
	if(position.second%2)
	{
		bgGetGfxPtr(background)[SCREEN_WIDTH/2 + (position.first/2) + (position.second/2)*SCREEN_WIDTH] = pixValue;
	}
	else
	{
		bgGetGfxPtr(background)[(position.first/2) + (position.second/2)*SCREEN_WIDTH] = pixValue;
	}
}

void Line::draw(int background, int color)
{

	// Bresenham's line algorithm
	const bool steep = (abs(end.second - start.second) > abs(end.first - end.first));
	if(steep)
	{
		std::swap(start.first, start.second);
		std::swap(end.first, end.second);
	}

	if(start.first > end.first)
	{
		std::swap(start.first, end.first);
		std::swap(start.second, end.second);
	}

	const int dx = end.first - start.first;
	const int dy = abs(end.second - start.second);

	float error = dx / 2.0f;
	const int ystep = (start.second < end.second) ? 1 : -1;
	int y = (int)start.second;

	const int maxX = (int)end.first;

	for(int x=(int)start.first; x<maxX; x++)
	{
		if(steep)
		{
			drawPixel({y,x}, background, color);
		}
		else
		{
			drawPixel({x,y}, background, color);
		}

		error -= dy;
		if(error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}
