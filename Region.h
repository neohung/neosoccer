#ifndef REGION_H
#define REGION_H
#include <algorithm> //max,min
#include "util.h"
#include "neogdi.h"
#include "V2D.h"
class Region
{
private:
	double m_dTop;
	double m_dRight;
	double m_dLeft;
	double m_dBottom;
	V2D m_vCenter;
	double m_dWidth;
	double m_dHeight;
	int m_iID;
public:
	Region(double left,
           double top,
           double right,
           double bottom,
           int id = -1):m_dTop(top),
                        m_dRight(right),
                        m_dLeft(left),
                        m_dBottom(bottom),
                        m_iID(id)
  {
    m_vCenter = V2D( (left+right)*0.5, (top+bottom)*0.5 );
    m_dWidth  = fabs(right-left);
    m_dHeight = fabs(bottom-top);
  }
  double     Top()const{return m_dTop;}
  double     Bottom()const{return m_dBottom;}
  double     Left()const{return m_dLeft;}
  double     Right()const{return m_dRight;}
  double     Width()const{return fabs(m_dRight - m_dLeft);}
  double     Height()const{return fabs(m_dTop - m_dBottom);}
  double     Length()const{return std::max(Width(), Height());}
  double     Breadth()const{return std::min(Width(), Height());}
  V2D  Center()const{return m_vCenter;}
  int       ID()const{return m_iID;}
  inline void Render(bool ShowID = 0)const
  {
    ngdi->HollowBrush();
    ngdi->GreenPen();
    ngdi->Rect(V2D(m_dLeft, m_dTop), V2D(m_dRight, m_dBottom));
    if (ShowID)
    { 
      ngdi->TextColor(NEOgdi::green);
      ngdi->TextAtPos(Center(), ttos(ID()));
    }
  }
};
#endif