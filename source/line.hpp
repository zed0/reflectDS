#ifndef LINE_HPP
#define LINE_HPP

#include <nds.h>

#include <utility>
#include <cmath>

class Line
{
	public:
		Line(std::pair<float, float> start, std::pair<float, float> end);
		void drawPixel(std::pair<int,int> position, int background, int color);
		void draw(int background, int color);
        std::pair<float,float> circleCollide(std::pair<float, float> position, float radius);
        std::pair<float,float> getNormal();
        float getLength();
	protected:
	private:
		std::pair<float, float> start;
		std::pair<float, float> end;
};

#endif
