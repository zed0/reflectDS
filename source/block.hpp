#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <nds.h>
#include <utility>

class Block
{
	public:
		Block(int id, int color, std::pair<int,int> position, std::pair<int,int> size);
		void draw();
		bool getCollision(std::pair<int, int> point);
		void setPosition(std::pair<int, int> position);
		bool destroyed;
	protected:
	private:
		int id;
		u16 *gfx, *gfxSub;
		std::pair<int, int> position;
		std::pair<int, int> size;
};

#endif
