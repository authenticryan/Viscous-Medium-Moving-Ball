#include "gl_helper.h"
//#include "GL/glew.h"
#include <GL/glu.h>


void gl_helper::DebugPoint(float x , float y){

    float SavedColor[4];
    glGetFloatv(GL_CURRENT_COLOR, SavedColor);


    glColor4f(1.0f,0,0,1.0f);

            glBegin(GL_POINTS);
              glVertex2f(x , y);
            glEnd();

   glColor4f(SavedColor[0],SavedColor[1],SavedColor[2],SavedColor[3]);

}


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



void gl_helper::DrawNumber(int x , int y , int n)
{

/*
//Top
DrawRect(x + 5 , y , 20 , 5  );
//Top Left
DrawRect(x , y + 5 , 5 , 20  );
//Top Right
DrawRect(x + 25 , y + 5 , 5 , 20 );
//Center
DrawRect(x + 5 , y + 25 , 20 , 5  );
//Buttom Left
DrawRect(x , y + 30 , 5 , 20  );
//Buttom Right
DrawRect(x + 25 , y + 30 , 5 , 20 );
//Buttom
DrawRect(x + 5 , y + 50 , 20 , 5  );
*/


    switch(n){

    case 0:
        DrawRect(x + 5 , y , 20 , 5  );
        DrawRect(x , y + 5 , 5 , 20  );
        DrawRect(x + 25 , y + 5 , 5 , 20 );
        DrawRect(x , y + 30 , 5 , 20  );
        DrawRect(x + 25 , y + 30 , 5 , 20 );
        DrawRect(x + 5 , y + 50 , 20 , 5  );
        break;

    case 1:
        DrawRect(x + 25 , y + 5 , 5 , 20 );
        DrawRect(x + 25 , y + 30 , 5 , 20 );
        break;
    case 2:
        DrawRect(x + 5 , y , 20 , 5  );
        DrawRect(x + 25 , y + 5 , 5 , 20 );
        DrawRect(x + 5 , y + 25 , 20 , 5  );
        DrawRect(x , y + 30 , 5 , 20  );
        DrawRect(x + 5 , y + 50 , 20 , 5  );
        break;
    case 3:
        DrawRect(x + 5 , y , 20 , 5  );
        DrawRect(x + 25 , y + 5 , 5 , 20 );
        DrawRect(x + 5 , y + 25 , 20 , 5  );
        DrawRect(x + 25 , y + 30 , 5 , 20 );
        DrawRect(x + 5 , y + 50 , 20 , 5  );
        break;
    case 4:
        DrawRect(x , y + 5 , 5 , 20  );
        DrawRect(x + 25 , y + 5 , 5 , 20 );
        DrawRect(x + 5 , y + 25 , 20 , 5  );
        DrawRect(x + 25 , y + 30 , 5 , 20 );
        break;
    case 5:
        DrawRect(x + 5 , y , 20 , 5  );
        DrawRect(x , y + 5 , 5 , 20  );
        DrawRect(x + 5 , y + 25 , 20 , 5  );
        DrawRect(x + 25 , y + 30 , 5 , 20 );
        DrawRect(x + 5 , y + 50 , 20 , 5  );
        break;
    case 6:
        DrawRect(x + 5 , y , 20 , 5  );
        DrawRect(x , y + 5 , 5 , 20  );
        DrawRect(x + 5 , y + 25 , 20 , 5  );
        DrawRect(x , y + 30 , 5 , 20  );
        DrawRect(x + 25 , y + 30 , 5 , 20 );
        DrawRect(x + 5 , y + 50 , 20 , 5  );
        break;
    case 7:
        DrawRect(x + 5 , y , 20 , 5  );
        DrawRect(x , y + 5 , 5 , 20  );
        DrawRect(x + 25 , y + 5 , 5 , 20 );
        DrawRect(x + 25 , y + 30 , 5 , 20 );
        break;
    case 8:
        DrawRect(x + 5 , y , 20 , 5  );
        DrawRect(x , y + 5 , 5 , 20  );
        DrawRect(x + 25 , y + 5 , 5 , 20 );
        DrawRect(x + 5 , y + 25 , 20 , 5  );
        DrawRect(x , y + 30 , 5 , 20  );
        DrawRect(x + 25 , y + 30 , 5 , 20 );
        DrawRect(x + 5 , y + 50 , 20 , 5  );
        break;
    case 9:
        DrawRect(x + 5 , y , 20 , 5  );
        DrawRect(x , y + 5 , 5 , 20  );
        DrawRect(x + 25 , y + 5 , 5 , 20 );
        DrawRect(x + 5 , y + 25 , 20 , 5  );
        DrawRect(x + 25 , y + 30 , 5 , 20 );
        DrawRect(x + 5 , y + 50 , 20 , 5  );
        break;

    }



}
