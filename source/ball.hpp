#ifndef BALL_HPP
#define BALL_HPP

#include <nds.h>

#include <utility>
#include <vector>

#include "block.hpp"

enum side_t{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

class Ball
{
	public:
		Ball(int id, int color, std::pair<float,float> position, std::pair<int, int> size);
		void draw();
		void tick(int time);
		void setVelocity(std::pair<float, float> velocity);
		std::pair<float, float> getVelocity();
		std::pair<float, float> getPosition();
		std::pair<float, float> getPosition(side_t side);
		void collide(Block& block);
	protected:
	private:
		int id;
		u16 *gfx, *gfxSub;
		std::pair<float, float> position;
		std::pair<int, int> size;
		std::pair<float, float> velocity;
};

#endif
