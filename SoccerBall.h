#ifndef SOCCERBALL_H
#define SOCCERBALL_H
#include "MovingObj.h"
class SoccerBall: public MovingObject
{
private:
	 V2D m_vOldPos;
public:
	void Update(double time){}
	void Render(){}
};

#endif