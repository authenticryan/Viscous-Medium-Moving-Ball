#include "gl_helper.h"
//#include "GL/glew.h"
#include <GL/glu.h>




void gl_helper::DrawRect(int x, int y, int width, int height)
{


   glBegin(GL_QUADS);

     //Buttom Left
     glVertex2f(x , y);
     //Buttom Right
     glVertex2f(x + width , y);
     //Top Right
     glVertex2f(x + width , y + height );

     glVertex2f(x , y + height );

   glEnd();


}



