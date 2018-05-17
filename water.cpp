#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include "gl_helper.h"
#include <time.h>

// Variable declaration for the the waves
#define BOUNDS    1
#define WATERSIZE 450

int damp = 10;
float water[2][WATERSIZE][WATERSIZE];

int spin_x, spin_y, spin_z; /* x-y rotation and zoom */
int h, w;                    /* height, width  of window */
int old_x, old_y, move_z;
int depth = 3;
int i = 0, counter = 0;
// End of variable declaration for the ripples

int red = 0 , green = 0, blue = 1;

// for the ping pong program  
// starts here -----------------------
const int width = 450 , height = 450 ;
const int RacketWidth = 10 , RacketHeight = 460;
const int BallWidth = 10 , BallHeight = 10;

double time1;

int LeftY=0;
int RightY=0;

int ballX,ballY;
int ballVelocityX = 4;
float ballVelocityY =0.0f;
float StoredVelocity = 0.0f;


void Reset();
void Collisions();
bool Between(int target, int min , int max );

// ends here --------------------------------

clock_t this_time = clock();
clock_t last_time = this_time;

const int NUM_SECONDS = .2;
double time_counter = 0;


int t = 0, f = 1;

void calcwater() {
	int x, y;
	float n;
	for(y = 1; y < WATERSIZE-1; y++) {
		for(x = 1; x < WATERSIZE-1; x++) {
			n = ( water[t][x-1][y] +
				  water[t][x+1][y] + 
				  water[t][x][y-1] + 
				  water[t][x][y+1]
				  ) /2;
			n -= water[f][x][y];
      		n = n - (n / damp);
			water[f][x][y] = n;
		}
	}

	y = 0;
	for(x = 1; x < WATERSIZE-1; x++) {
			n = ( water[t][x-1][y] +
				  water[t][x+1][y] + 
				  water[t][x][y+1]
				  ) /2;
			n -= water[f][x][y];
      		n = n - (n / damp);
			water[f][x][y] = n;
	}
	
	
	x = 0;
	for(y = 1; y < WATERSIZE-1; y++) {
			n = ( water[t][x+1][y] + 
				  water[t][x][y-1] + 
				  water[t][x][y+1]
				  ) /2;
			n -= water[f][x][y];
      		n = n - (n / damp);
			water[f][x][y] = n;
	}

	x = WATERSIZE-1;
	for(y = 1; y < WATERSIZE-1; y++) {
			n = ( water[t][x-1][y] +
				  water[t][x][y-1] + 
				  water[t][x][y+1]
				  ) /2;
			n -= water[f][x][y];
      		n = n - (n / damp);
			water[f][x][y] = n;
	}
	y = WATERSIZE-1;
	for(x = 1; x < WATERSIZE-1; x++) {
			n = ( water[t][x-1][y] +
				  water[t][x+1][y] + 
				  water[t][x][y-1] 
				  ) /2;
			n -= water[f][x][y];
      		n = n - (n / damp);
			water[f][x][y] = n;
	}

}

void init();

void reshape(int width, int height) {
    w = width;
    h = height;

    glViewport(0, 0, 450, 450);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 1.0, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
}

void Collisions(){

	this_time = clock();
	time_counter += (double)(this_time - last_time);
	last_time = this_time;

    if(time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC) ){

		time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);

        ballX += ballVelocityX;

        StoredVelocity += ballVelocityY;


        // To ensure that the ball bounces
        if(StoredVelocity > 10.0f){
            ballY+=1;
            StoredVelocity-=10;
        }else if(StoredVelocity < -10.0f){
            ballY-=1;
            StoredVelocity+=10;

        }
    }


    //Ball at Right Edge
    if( ballX > 430 ){
            ballVelocityX= -ballVelocityX;

    //Ball at Left Edge
    }else if( ballX < 10 ){
            ballVelocityX= -ballVelocityX;

    //Ball at bottom Edge
    }else if( ballY < 0 ){

        ballY = 0;
        ballVelocityY= -ballVelocityY;

    //Ball at top Edge
    }else if( ballY > 440 ){

        ballY = 440;
        ballVelocityY = -ballVelocityY;
    }

	water[f][(ballX+5)%WATERSIZE][(ballY+5)%WATERSIZE] = -100;

}


void display(void) {
    int i, j, tmp;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Code from main.cpp
		
		glPushMatrix();

        glLoadIdentity();
        glOrtho(0 , 450 , 0 , 450 , 0 , 1);

		// Set color properties
        glClearColor(0.0f, 0.0f, 0.0f, 0);
        glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0, 1.0, 1.0);

		//Left Racket
        gl_helper::DrawRect( 0 , LeftY, RacketWidth , RacketHeight  );
        //Right Racket
        gl_helper::DrawRect( width - 10 , RightY , RacketWidth , RacketHeight  );
        //Ball
        gl_helper::DrawRect( ballX , ballY , BallWidth , BallHeight  );

        //Collision Detection
        Collisions();

		glPopMatrix();
	// end of code from main.cpp

	glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0, 0, spin_z-220);
    glRotatef(spin_x, 0, 1, 0);
    glRotatef(spin_y, 1, 0, 0);

    
	calcwater();
	glBegin(GL_POINTS);
	for(i = 0; i < WATERSIZE; i++) {
		for(j = 0; j < WATERSIZE; j++) {
				glColor3f(red, green,blue);
    			glVertex3f(j-WATERSIZE/2, i-WATERSIZE/2, water[t][j][i]);
		}
	}
	glEnd();

	tmp = t; t = f; f = tmp;

    glPopMatrix();
 
	glutSwapBuffers();
}

int num  = 0;
int delay = 70;
void idle(void)
{
	// To ensure that the waves are periodically updated
    glutPostRedisplay();
}

void init(void) {
	int i, j;

    glEnable(GL_DEPTH_TEST);

	for( i = 0; i < WATERSIZE; i++) 
		for( j = 0; j < WATERSIZE; j++) {
			water[0][j][i] = 0;
			water[1][j][i] = 0;
		}
}

void
keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case '1':
				// water
				red = 0;
				green = 0;
				blue = 1;
				damp = 10;
            break;
        case '2':
				// oil
                damp = 100;		
				red = 1; 
				green = 1;
				blue = 0;
            break;
        case '3':
				// rubbing alchol
				red = 1;
				green = 1;
				blue = 1;
				damp = 5;
            break;
		case '0':
				// exit the system
                exit(0);
			break;

    }
}



int
main(int argc, char** argv)
{

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(width, height);
    glutInit(&argc, argv);


    //Ball Starting position
    ballX = width/2 - 5 ;
    ballY = height/2 - 5;

    // initial ball velocity
    ballVelocityY= 10;
     
    // end of setting parameters from main.cpp

    glutCreateWindow("Particle in volumic mesh");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);


    glEnable(GL_DEPTH_TEST);

    if(argc == 2) {
        if (strcmp(argv[1], "-h") == 0) {
            fprintf(stderr, "%s [depth]\n", argv[0]);
            exit(0);
        }
        sscanf(argv[1], "%d", &depth);
    }

    init();

    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
