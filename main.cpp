//#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "gl_helper.h"
#include <iostream>

using namespace std;

const int width = 450 , height = 450 ;
const int RacketWidth = 10 , RacketHeight = 100;
const int BallWidth = 10 , BallHeight = 10;

double time1;

int LeftY=0;
int RightY=0;
int Racketspeed=5;

int ballX,ballY;
int ballVelocityX = 1;
float ballVelocityY =0.0f;
float StoredVelocity = 0.0f;

//Ball Speed
double TimeSpeed=0.2;

int LeftScore = 0;
int RightScore = 0;

void Reset();
void Collisions();
bool Between(int target, int min , int max );

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods){

//Left Control UP
    if(key == GLFW_KEY_UP){
        RightY-=Racketspeed;}
//Left Control Down
    if(key == GLFW_KEY_DOWN){
        RightY+=Racketspeed;}
//Right Control UP
    if(key == GLFW_KEY_W){
        LeftY-=Racketspeed;}
//Right Control Down
    if(key == GLFW_KEY_S){
        LeftY+=Racketspeed;}

}


int main()
{

    GLFWwindow* window;

    glfwInit();

    //Hints Before Window Creation
    glfwWindowHint(GLFW_RESIZABLE , GL_FALSE );

    window = glfwCreateWindow( width , height , "Pong" , NULL , NULL );
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback( window , KeyCallBack );


     //Ball Starting position
     ballX = width/2 - 5 ;
     ballY = height/2 - 5;

     //Racket Starting Y Position
     LeftY = height/2 - 50;
     RightY = height/2 - 50;

     time1 = glfwGetTime()*TimeSpeed;


    while( !glfwWindowShouldClose(window) ){

        //2D Mode

        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        glOrtho(0 , width , height , 0 , 0 , 1);

        glDisable(GL_DEPTH_TEST);

        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        glClearColor(0.0f, 0.0f, 0.0f, 0);

        glClear(GL_COLOR_BUFFER_BIT);

        //Collision Detection
        Collisions();

        //Left Racket
        gl_helper::DrawRect( 0 , LeftY, RacketWidth , RacketHeight  );
        //Right Racket
        gl_helper::DrawRect( width - 10 , RightY , RacketWidth , RacketHeight  );
        //Ball
        gl_helper::DrawRect( ballX , ballY , BallWidth , BallHeight  );

        //Left Score
        gl_helper::DrawNumber( width/2 - 40 , 10 , LeftScore );
        //Right Score
        gl_helper::DrawNumber( width/2 + 10 , 10 , RightScore );
        //Colon
        gl_helper::DrawRect( width/2 - 2 , 25 , 5 , 5 );
        gl_helper::DrawRect( width/2 - 2 , 45 , 5 , 5 );

        glfwSwapBuffers(window);
        glfwSwapInterval(1);
        glfwPollEvents();

    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void Collisions(){

    if( glfwGetTime() - time1 > 1.0 ){

        time1 = glfwGetTime()*TimeSpeed;

        ballX += ballVelocityX;

        StoredVelocity += ballVelocityY;

        if(StoredVelocity > 1.0f){
            ballY+=1;
            StoredVelocity-=1;
        }else if(StoredVelocity < -1.0f){
            ballY-=1;
            StoredVelocity+=1;

        }
    }


    //Ball at Right Edge
    if( ballX > width - RacketWidth*2 ){

        if( Between(ballY, RightY + RacketHeight, RightY )  ){

            ballVelocityX= -ballVelocityX;

            if( Between(ballY, RightY, RightY + RacketHeight*0.3 ) ){

                ballVelocityY-=0.3;

            }else if( Between(ballY,  RightY + RacketHeight - RacketHeight*0.3 , RightY + RacketHeight ) ){

                ballVelocityY+=0.3;

            }


        }else{

            LeftScore++;
            Reset();

        }

    //Ball at Left Edge
    }else if( ballX < RacketWidth ){

        if( Between(ballY, LeftY + RacketHeight, LeftY )  ){

            ballVelocityX= -ballVelocityX;

            if( Between(ballY, LeftY, LeftY + RacketHeight*0.3 ) ){

                ballVelocityY-=0.3;

            }else if( Between(ballY,  LeftY + RacketHeight - RacketHeight*0.3 , RightY + RacketHeight ) ){

                ballVelocityY+=0.3;
            }

        }else{

            RightScore++;
            Reset();

        }

    //Ball at Top Edge
    }else if( ballY < 0 ){

        ballY = 0;
        ballVelocityY= -ballVelocityY;

    //Ball at Buttom Edge
    }else if( ballY > height - BallHeight ){

        ballY = height - BallHeight;
        ballVelocityY= -ballVelocityY;

    }

}


bool Between(int target, int a , int b ){

int max;
int min;

if( a > b){

    max = a;
    min = b;

}else{
    max=b;
    min=a;
}

     if( target < max && target > min)
        return true;

 return false;

}

void Reset(){

    ballX = width/2 - BallWidth/2 ;
    glfwSetTime(0.0);
    time1=0.0;
    ballVelocityX=1;
    ballVelocityY=0;
    StoredVelocity=0;

    if(LeftScore > 9 || RightScore > 9){

        LeftScore = 0;
        RightScore = 0;
    }
}

