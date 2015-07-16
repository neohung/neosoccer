#ifndef SOCCERPITCH_H
#define SOCCERPITCH_H
#include "util.h"
#include "neogdi.h"
#include "wall.h"
#include "Region.h"
//
class Goal 
{
private:
  V2D   m_vLeftPost;
  V2D   m_vRightPost;
  //a vector representing the facing direction of the goal
  V2D   m_vFacing;
  //the position of the center of the goal line
  V2D   m_vCenter;
  //得分數
  int   m_iNumGoalsScored;
public:

  Goal(V2D left, V2D right, V2D facing):m_vLeftPost(left),
                                        m_vRightPost(right),
                                        m_vCenter((left+right)/2.0),
                                        m_iNumGoalsScored(0),
                                        m_vFacing(facing)
  {  }
  double GoalWidth()const{return m_vLeftPost.y - m_vRightPost.y;}
  V2D Center()const{return m_vCenter;}
  V2D Facing()const{return m_vFacing;}
  V2D LeftPost()const{return m_vLeftPost;}
  V2D RightPost()const{return m_vRightPost;}
  int NumGoalsScored()const{return m_iNumGoalsScored;}
  void ResetGoalsScored(){m_iNumGoalsScored = 0;}
  /*
  //檢查是否得分
  bool Scored(const SoccerBall*const ball)
  {
    if (LineIntersection2D(ball->Pos(), ball->OldPos(), m_vLeftPost, m_vRightPost))
    {
      ++m_iNumGoalsScored;
      return true;
    }
    return false;
  }
  */
};
//
class SoccerPitch
{
private:
	int m_cxClient;
	int m_cyClient;
	bool m_bPaused;
	std::vector<Wall> m_vecWalls;
	Region* m_pPlayingArea;
	Goal* m_pRedGoal;
    Goal* m_pBlueGoal;
public:
	SoccerPitch(int cx,int cy);
	~SoccerPitch();
	void Update(double timeElapsed);
	void Render();
};
#endif