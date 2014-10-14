#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <nds.h>

class Block
{
	public:
		Block(int id, int color, int x, int y);
		void draw();
		int getCollision();
	protected:
	private:
		int id;
		u16* gfx;
		int x, y;
};

#endif
