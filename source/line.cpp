#include "line.hpp"

Line::Line(std::pair<float, float> start, std::pair<float, float> end)
{
	this->start = start;
	this->end = end;
}

void Line::drawPixel(std::pair<int,int> position, int background, int color)
{
    position.second -= SCREEN_HEIGHT;
    int index = ((int)position.first/2) + ((int)position.second/2)*SCREEN_WIDTH;
    if((int)position.second%2)
    {
        index += SCREEN_WIDTH/2;
    }
    int pixValue = bgGetGfxPtr(background)[index];
    if((int)position.first%2)
	{
        pixValue &= 0x0F;
		pixValue |= color<<8;
	}
	else
	{
        pixValue &= 0xF0;
		pixValue |= color;
	}
    bgGetGfxPtr(background)[index] = pixValue;
}

void Line::draw(int background, int color)
{
    //Bresenham's Line algorithm:
    int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
    dx=end.first-start.first;
    dy=end.second-start.second;
    dx1=fabs(dx);
    dy1=fabs(dy);
    px=2*dy1-dx1;
    py=2*dx1-dy1;
    if(dy1<=dx1)
    {
        if(dx>=0)
        {
            x=start.first;
            y=start.second;
            xe=end.first;
        }
        else
        {
            x=end.first;
            y=end.second;
            xe=start.first;
        }
        drawPixel({x,y},background,color);
        for(i=0;x<xe;i++)
        {
            x=x+1;
            if(px<0)
            {
                px=px+2*dy1;
            }
            else
            {
                if((dx<0 && dy<0) || (dx>0 && dy>0))
                {
                    y=y+1;
                }
                else
                {
                    y=y-1;
                }
                px=px+2*(dy1-dx1);
            }
            drawPixel({x,y},background,color);
        }
    }
    else
    {
        if(dy>=0)
        {
            x=start.first;
            y=start.second;
            ye=end.second;
        }
        else
        {
            x=end.first;
            y=end.second;
            ye=start.second;
        }
        drawPixel({x,y},background,color);
        for(i=0;y<ye;i++)
        {
            y=y+1;
            if(py<=0)
            {
                py=py+2*dx1;
            }
            else
            {
                if((dx<0 && dy<0) || (dx>0 && dy>0))
                {
                    x=x+1;
                }
                else
                {
                    x=x-1;
                }
                py=py+2*(dx1-dy1);
            }
            drawPixel({x,y},background,color);
        }
    }
}

std::pair<float,float> Line::circleCollide(std::pair<float, float> position, float radius)
{
    //returns {-1,-1} if no intersection
    std::pair<float, float> result = {-1,-1};
    //line segment goes from (start.first,start.second) to (end.first,end.second) 2   //the test point is at (x,y)
    float A = position.first - start.first;//vector from one end point to the test point
    float B = position.second - start.second;
    float C = end.first - start.first;//vector from one end point to the other end point
    float D = end.second - start.second;
     
    float dot = A * C + B * D;//some interesting math coming from the geometry of the algorithm
    float len_sq = C * C + D * D;
    float param = dot / len_sq;
     
    std::pair<float, float> closest; //the coordinates of the point on the line segment closest to the test point
     
    //the parameter tells us which point to pick
    //if it is outside 0 to 1 range, we pick one of the endpoints
    //otherwise we pick a point inside the line segment
    if(param < 0)
    {
        closest = start;
    }
    else if(param > 1)
    {
        closest = end;
    }
    else
    {
        closest.first = start.first + param * C;
        closest.second = start.second + param * D;
    }
    float dx = position.first-closest.first;
    float dy = position.second-closest.second;
    float dist = sqrt(dx*dx + dy*dy);//distance from the point to the segment
    if(dist < radius)
    {
        result = closest;
    }
    return result;
}

std::pair<float,float> Line::getNormal()
{
    std::pair<float,float> result;
    std::pair<float,float> difference;
    difference.first = end.first-start.first;
    difference.second = end.second-start.second;
    result.first=-difference.second;
    result.second=difference.first;
    return result;
}

float Line::getLength()
{
    std::pair<float,float> distance;
    distance.first = end.first-start.first;
    distance.second = end.second-start.second;
    return sqrt(distance.first*distance.first + distance.second*distance.second);
}
