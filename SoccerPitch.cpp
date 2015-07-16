#include "SoccerPitch.h"

SoccerPitch::SoccerPitch(int cx, int cy): m_cxClient(cx),
										  m_cyClient(cy),
										  m_bPaused(false)				
{
  //GoalWidth指的是得分區厚度
  int GoalWidth = 200;
  m_pPlayingArea = new Region(20, 20, cx-20, cy-20);	
  //
   m_pRedGoal  = new Goal(V2D(m_pPlayingArea->Left(), (cy-GoalWidth)/2),
                          V2D(m_pPlayingArea->Left(), cy - (cy-GoalWidth)/2),
                          V2D(1,0));
  m_pBlueGoal = new Goal(V2D( m_pPlayingArea->Right(), (cy-GoalWidth)/2),
                          V2D(m_pPlayingArea->Right(), cy - (cy-GoalWidth)/2),
                          V2D(-1,0));							  	
  //建立外牆
  V2D TopLeft(m_pPlayingArea->Left(), m_pPlayingArea->Top());                                        
  V2D TopRight(m_pPlayingArea->Right(), m_pPlayingArea->Top());
  V2D BottomRight(m_pPlayingArea->Right(), m_pPlayingArea->Bottom());
  V2D BottomLeft(m_pPlayingArea->Left(), m_pPlayingArea->Bottom());                                   
  m_vecWalls.push_back(Wall(BottomLeft, m_pRedGoal->RightPost()));
  m_vecWalls.push_back(Wall(m_pRedGoal->LeftPost(), TopLeft));
  m_vecWalls.push_back(Wall(TopLeft, TopRight));
  m_vecWalls.push_back(Wall(TopRight, m_pBlueGoal->LeftPost()));
  m_vecWalls.push_back(Wall(m_pBlueGoal->RightPost(), BottomRight));
  m_vecWalls.push_back(Wall(BottomRight, BottomLeft));

}
SoccerPitch::~SoccerPitch()
{

}
void SoccerPitch::Update(double timeElapsed)
{

}
void SoccerPitch::Render()
{
  ngdi->TransparentText();
  ngdi->HollowBrush();
  //畫草地
  ngdi->DarkGreenPen();
  ngdi->DarkGreenBrush();
  ngdi->Rect(V2D(0,0),V2D(m_cxClient, m_cyClient));
  //畫球門
  ngdi->HollowBrush();
  ngdi->RedPen();
  ngdi->Rect(V2D(m_pPlayingArea->Left(), (m_cyClient-m_pBlueGoal->GoalWidth())/2), V2D(m_pPlayingArea->Left()+40, m_cyClient - (m_cyClient-m_pBlueGoal->GoalWidth())/2));
  ngdi->BluePen();
  ngdi->Rect(V2D(m_pPlayingArea->Right(), (m_cyClient-m_pRedGoal->GoalWidth())/2), V2D(m_pPlayingArea->Right()-40, m_cyClient - (m_cyClient-m_pRedGoal->GoalWidth())/2)); 
  //render the pitch markings
  //畫球場中間圓線
  ngdi->WhitePen();
  ngdi->Circle(m_pPlayingArea->Center(), m_pPlayingArea->Width() * 0.125);
  //畫球場中線
  ngdi->Line(V2D(m_pPlayingArea->Center().x, m_pPlayingArea->Top()), V2D(m_pPlayingArea->Center().x, m_pPlayingArea->Bottom()));
  ngdi->WhiteBrush();
  //畫球場中間小圓
  ngdi->Circle(m_pPlayingArea->Center(), 2.0);
  //the ball
  //gdi->WhitePen();
  //gdi->WhiteBrush();
  //m_pBall->Render();
  //Render the teams
  //m_pRedTeam->Render();
  //m_pBlueTeam->Render(); 

  //render the walls
  ngdi->WhitePen();
  for (unsigned int w=0; w<m_vecWalls.size(); ++w)
  {
    m_vecWalls[w].Render();
  }

  //show the score
  ngdi->TextColor(NEOgdi::red);
  //gdi->TextAtPos((m_cxClient/2)-50, m_cyClient-18, "Red: " + ttos(m_pBlueGoal->NumGoalsScored()));
  ngdi->TextAtPos((m_cxClient/2)-50, m_cyClient-18, L"Red: " + ttos(99));

  ngdi->TextColor(NEOgdi::blue);
  //ngdi->TextAtPos((m_cxClient/2)+10, m_cyClient-18, "Blue: " + ttos(m_pRedGoal->NumGoalsScored())); 
  ngdi->TextAtPos((m_cxClient/2)+10, m_cyClient-18, L"Blue: " + ttos(99));
}