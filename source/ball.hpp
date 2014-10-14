#ifndef BALL_HPP
#define BALL_HPP

#include <nds.h>
#include <utility>

enum side_t{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

class Ball
{
	public:
		Ball(int id, int color, std::pair<int,int> position, std::pair<int, int> size);
		void draw();
		void tick(int time);
		void setVelocity(std::pair<int, int> velocity);
		std::pair<int, int> getVelocity();
		std::pair<int, int> getPosition(side_t side);
	protected:
	private:
		int id;
		u16 *gfx, *gfxSub;
		std::pair<int, int> position;
		std::pair<int, int> size;
		std::pair<int, int> velocity;
};

#endif
