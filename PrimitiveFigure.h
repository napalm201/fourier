#define TWO_PI 6.2831853
#include "Vec2.h"

namespace PrimitiveFigure
{
  static float width = 1;
  static int partition = 40;

  void drawCircle(float r, float posX, float posY)
  {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    glBegin(GL_LINE_LOOP);

    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(width);

    for(int n = 0; n < partition - 1; n++){
     	float x = r * cos(TWO_PI * n / partition);
     	float y = r * sin(TWO_PI * n / partition);
      glVertex2f(x, y);
    }

    glEnd();

    glPopMatrix();
  }

  void drawLine(float posX1, float posX2, float posY1, float posY2)
  {

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(width);
    glVertex2f(posX1, posY1);
    glVertex2f(posX2, posY2);
    glEnd();

  }

  void curveLines(std::vector<Vec2> line){

   glBegin(GL_LINE_STRIP);
   glColor3f(1.0f, 0.0f, 1.0f);
   glLineWidth(width);

   for(auto point : line){
    glVertex2f(point.x, point.y);
   }

   glEnd();
  }
}