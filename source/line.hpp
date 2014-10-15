#ifndef LINE_HPP
#define LINE_HPP

#include <nds.h>

#include <utility>
#include <cmath>

class Line
{
	public:
		Line(std::pair<int, int> start, std::pair<int, int> end);
		void draw(int background);
	protected:
	private:
		std::pair<int, int> start;
		std::pair<int, int> end;
};

#endif
